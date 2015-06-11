<?hh // strict
namespace Decouple\CLI\Command;
/**
 * This software is maintained voluntarily under the MIT license.
 * For more information, see <http://www.decouple.io/>
 */

/**
 * An Abstract Command Container
 *
 * @author Andrew Ewing <drew@phenocode.com>
 */
abstract class AbstractCommand implements CommandInterface {
  /**
   * The command name (i.e. app:version)
   */
  public static string $name = '';
  /**
   * Get the name of the Command object
   * @return string
   */
  public static function getName() : string {
    return static::$name;
  }
  /**
   * Execute the Command
   * @return mixed
   */
  abstract public function execute() : mixed;
}
