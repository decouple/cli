<?hh // strict
namespace Decouple\CLI\Request;
/**
 * This software is maintained voluntarily under the MIT license.
 * For more information, see <http://www.decouple.io/>
 */

/**
 * CLI Request Container
 * Used to parse all command line arguments, flags, options, their values.
 *
 * @author Andrew Ewing <drew@phenocode.com>
 */
class Request {
  /**
   * A vector containing all command line arguments
   */
  protected Vector<Argument> $arguments;
  /**
   * Create a new CLI Request
   * @param  Vector<string> $args A Vector of tokenized command line arguments
   */
  public function __construct(Vector<string> $args) {
    $this->arguments = Vector {};
    foreach($args as $arg) {
      $this->arguments->add(new Argument($arg));
    }
  }
  /**
   * Get the command line options
   * @return Vector<Argument>   A Vector of command line options
   */
  public function getOptions() : Vector<Argument> {
    return $this->getByType(Argument::OPTION);
  }
  /**
   * Get the command line flags
   * @return Vector<Argument>   A Vector of command line flags
   */
  public function getFlags() : Vector<Argument> {
    return $this->getByType(Argument::FLAG);
  }
  /**
   * Get the command line arguments
   * @return Vector<Argument>   A Vector of command line arguments
   */
  public function getArgs() : Vector<Argument> {
    return $this->getByType(Argument::ARGUMENT);
  }
  /**
   * Get command line arguments by ArgumentType
   * @param  ArgumentType $type   Decouple\CLI\Request\Argument::ARGUMENT, ::FLAG, or ::OPTION
   * @return Vector<Argument>     A Vector containing matching arguments
   */
  public function getByType(ArgumentType $type) : Vector<Argument> {
    $arguments = Vector {};
    foreach($this->arguments as $argument) {
      if($argument->getType() === $type) {
        $arguments->add($argument);
      }
    }
    return $arguments;
  }
  /**
   * Get an argument by index or variable name
   * @param  mixed $seek    Index (int) or variable name (string)
   * @return Argument       The matching argument, throws an exception otherwise
   */
  public function getArg(mixed $seek) : Argument {
    if(is_int($seek)) {
      if(!$this->arguments->containsKey($seek)) {
        throw new InvalidRequestException(sprintf("Argument not found at index %s", $seek));
      }
      return $this->arguments->at($seek);
    } else if(is_string($seek)) {
      foreach($this->arguments as $argument) {
        if($argument->getVariable() == $seek) {
          return $argument;
        }
      }
    }
    throw new InvalidRequestException(sprintf("Argument not found: %s", $seek));
  }
  /**
   * Get the argument at the given index
   * @param  int $index   The index of the argument needed
   * @return Argument
   */
  public function at(int $index) : Argument {
    if(!$this->arguments->containsKey($index)) {
      throw new InvalidRequestException(sprintf("No argument found at index %s", $index));
    }
    return $this->arguments->at($index);
  }
}
