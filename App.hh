<?hh // strict
namespace Decouple\CLI;
/**
 * This software is maintained voluntarily under the MIT license.
 * For more information, see <http://www.decouple.io/>
 */
use Decouple\CLI\Request\Request;
use Decouple\Decoupler\Decoupler;
use Decouple\CLI\Command\AbstractCommand;
use Decouple\CLI\Command\AwaitableCommand;
use Decouple\CLI\Command\CommandInterface;
use Decouple\Registry\Registry;
use Decouple\Registry\Paths;
/**
 * CLI Application container for Decouple Framework.
 * Manages the registration and execution of command line operations.
 *
 * @author Andrew Ewing <drew@phenocode.com>
 */
class App {
  /**
   * The registered command line operations
   */
  protected Map<string, mixed> $commands;
  /**
   * The application configuration Registry
   */
  protected Map<string, Registry> $config;
  /**
   * Create a new CLI application container
   * @param  protected       Request        $request      Request element containing command line arguments
   * @param  protected       Decoupler      $decoupler    Decoupler injector instance
   * @param  public          Paths          $paths        A Registry containing application path information
   * @param  ?Vector<string> $commands=null A vector containing command:name => Command\Class
   */
  public function __construct(
    protected Request $request,
    protected Decoupler $decoupler,
    public Paths $paths,
    ?Vector<string> $commands = null,
  ) {
    $this->commands = Map {'decouple:version' => 'Decouple\CLI\Command\VersionCommand'};
    $this->config = Map {};
    if (!is_null($commands)) {
      $this->registerCommands($commands);
    }
  }
  /**
   * Execute the application container based on the given request and commands
   * @return mixed  Returns the result of the command execution
   */
  public function execute(): mixed {
    $command = $this->request->getArg(0)->getVariable();
    $command = $this->getCommand($command);
    if ($command instanceof AwaitableCommand) {
      return $command->execute()->getWaitHandle()->join();
    } else if ($command instanceof CommandInterface) {
      return $command->execute();
    }
    throw new \Exception(
      sprintf("Unable to inject command instance: %s", (string) $command),
    );
  }
  /**
   * Add a list of services to the application
   * @param KeyedTraversable<string,mixed> $services A keyed traversable containing serviceName => service
   */
  public function addServices(
    KeyedTraversable<string, mixed> $services,
  ): void {
    foreach ($services as $name => $service) {
      $this->addService($name, $service);
    }
  }
  /**
   * Add a service to the application
   * @param string $name          The name of the service
   * @param mixed  $service=true  The service class name or instance
   */
  public function addService(string $name, mixed $service = true): void {
    if ($service === true) {
      if (class_exists($name)) {
        $service = $this->decoupler->injectInstance($name);
      } else {
        throw new \Exception(
          sprintf(
            "Unable to automagically create service.\n Class %s is undefined.",
            $name,
          ),
        );
      }
    }
    if (!is_object($service)) {
      throw new \Exception(
        sprintf(
          "Services registered with HTTP must be objects! [%s is set to %s]",
          $name,
          (string) $service,
        ),
      );
    }
    $this->decoupler->set($name, $service);
  }
  /**
   * Register a vector of command classnames
   * @param  Vector<string> $commands     The command classnames
   * @return void
   */
  public function registerCommands(Vector<string> $commands): void {
    foreach ($commands as $command) {
      $this->registerCommand($command);
    }
  }
  /**
   * Register a command classname or instance
   * @param  mixed $command      A command classname or instance
   * @return void
   */
  public function registerCommand(string $command): void {
    if (!$command instanceof CommandInterface && !class_exists($command)) {
      throw new Command\CommandNotFoundException((string) $command);
    }
    if (!is_subclass_of($command, 'Decouple\CLI\Command\CommandInterface')) {
      throw new Command\CommandNotFoundException((string) $command);
    }
    $this->commands
      ->set(call_user_func_array([$command, 'getName'], []), $command);
  }
  /**
   * Get a command by name (throws an exception if not found)
   * @param  string $name         The name defined in the command class
   * @return CommandInterface     The command
   */
  public function getCommand(string $name): CommandInterface {
    if ($this->commands->contains($name)) {
      $command = $this->commands->at($name);
      $res = $this->decoupler->inject($command);
      if ($res instanceof CommandInterface) {
        return $res;
      }
    }
    throw new Command\CommandNotFoundException($name);
  }
  /**
   * Get an application configuration
   * @param  string $key                  The name of the configuration
   * @return Decouple\Registry\Registry   The registry container
   */
  public function getConfig(string $key): Registry {
    if ($this->config->contains($key)) {
      $reg = $this->config->get($key);
      if ($reg instanceof Registry) {
        return $reg;
      }
    } else {
      $config = hack_require(
        (string) $this->paths->get('config').
        '/'.
        str_replace('.', '/', $key).
        '.hh',
      );
      if ($config instanceof KeyedTraversable) {
        $reg = new Registry($config);
        $this->config->set($key, $reg);
        return $reg;
      }
    }
    return new Registry(Map {});
  }
  /**
   * Get the Application Decoupler instance
   * @return Decoupler The Decoupler instance
   */
  public function decoupler(): Decoupler {
    return $this->decoupler;
  }
}
