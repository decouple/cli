decouple/cli
===

Hack command line application container created for Decouple Framework.

## Usage
```php
<?hh // partial

use Decouple\CLI\App;
use Decouple\CLI\Request\Request;
use Decouple\Decoupler\Decoupler;
use Decouple\Registry\Paths;
use Decouple\Log\Log;

// Define a vector of valid commands
$commands = Vector {
  "Decouple\Test\TestCommand",
  "Decouple\DBAL_CLI\Command\MigrateUpCommand",
  "Decouple\DBAL_CLI\Command\MigrateDownCommand",
  "Decouple\DBAL_CLI\Command\MigrateRefreshCommand",
  "Decouple\DBAL_CLI\Command\SeedCommand"
};

// Remove the name of the binary .hh
$args = new Vector($argv);
if($args->get(0) == 'decouple.hh') { $args->removeKey(0); }

// Create the CLI Request
$request = new Request($args);

// Create a Decoupler injector instance
$decoupler = new Decoupler(Map {});

// Register a $paths container containing at least a path to the "config" dir
$paths = new Paths(Map {
  "config" => "/path/to/configs"
});

// Create the CLI App with the given Request,
$app = new App($request, $decoupler, new Paths($paths), $commands);

/**
* Using the Decoupler you can now add a parameter with any of the types below
* to your Command constructors and it will be automatically injected
*/
$services = Map {
  "Decouple\Log\Log" => new Log((string)$paths->get('logs') . "/cli.log"),
  "Decouple\Registry\Paths" => new Paths($paths),
  "Decouple\CLI\Request\Request" => $request
};
$app->addServices($services);

```
