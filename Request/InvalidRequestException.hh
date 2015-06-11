<?hh // strict
namespace Decouple\CLI\Request;
/**
 * This software is maintained voluntarily under the MIT license.
 * For more information, see <http://www.decouple.io/>
 */
use Exception;
/**
 * Invalid Request Exception
 * Used to notify CLI users of an invalid request
 *
 * @author Andrew Ewing <drew@phenocode.com>
 */
class InvalidRequestException extends Exception {
  public function __construct(string $message) {
    parent::__construct(sprintf("Invalid request; %s", $message));
  }
}
