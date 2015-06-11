<?hh // strict
namespace Decouple\CLI\Command;
/**
 * This software is maintained voluntarily under the MIT license.
 * For more information, see <http://www.decouple.io/>
 */

/**
 * The interface that CLI App Commands must adhere to
 */
interface CommandInterface {
  /**
   * Get the name of the Command
   * @return string   Command name
   */
  public static function getName() : string;
  /**
   * Execute the Command
   * @return mixed    The result of execution
   */
  public function execute() : mixed;
}
