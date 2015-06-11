<?hh // strict
namespace Decouple\CLI\Command;
/**
 * This software is maintained voluntarily under the MIT license.
 * For more information, see <http://www.decouple.io/>
 */
use Decouple\CLI\Console;
/**
 * Version Command
 *
 * @author Andrew Ewing <drew@phenocode.com>
 */
class VersionCommand extends AbstractCommand {
  /**
   * The name of the command
   */
  public static string $name = 'decouple:version';
  /**
   * Display the Decouple version number
   */
  public function execute() : void {
    Console::output(sprintf("Decouple v%s", "0.1a"));
  }
}
