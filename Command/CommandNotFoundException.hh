<?hh // strict
namespace Decouple\CLI\Command;
/**
 * This software is maintained voluntarily under the MIT license.
 * For more information, see <http://www.decouple.io/>
 */
use Exception;
/**
 * Command Not Found Exception
 * Used to notify CLI users that the requested command was not found
 *
 * @author Andrew Ewing <drew@phenocode.com>
 */
class CommandNotFoundException extends Exception {
  public function __construct(string $name) {
    $message = sprintf("Command not found: %s", $name);
    parent::__construct($message);
  }
}
