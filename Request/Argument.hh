<?hh // strict
namespace Decouple\CLI\Request;
/**
 * This software is maintained voluntarily under the MIT license.
 * For more information, see <http://www.decouple.io/>
 */
newtype ArgumentType = int;
/**
 * CLI Argument Container
 * Used to parse a command line argument, flag, or option, and it's value.
 *
 * @author Andrew Ewing <drew@phenocode.com>
 */
class Argument {
  /**
   * Command line argument type, used to provide expected input
   */
  const ArgumentType ARGUMENT = 0;
  /**
   * Command line flag type, used to toggle switching behavior
   */
  const ArgumentType FLAG = 1;
  /**
   * Command line option type, used to provide extra parameters with a value
   */
  const ArgumentType OPTION = 2;
  /**
   * The argument type of the current Argument object
   */
  protected ArgumentType $type;
  /**
   * The interpreted variable name of the current Argument object
   */
  protected string $variable;
  /**
   * The interpreted value (if applicable) of the current Argument object
   */
  protected mixed $value = false;
  /**
   * Create a new Argument object from a command line argument token
   * @param  string $text         The command line argument token
   */
  public function __construct(string $text) {
    if(substr($text, 0, 2) == '--') {
      $text = substr($text, 2);
      $this->type = Argument::OPTION;
      if (stristr($text,'=')) {
        list($this->variable, $this->value) = explode('=', $text);
      } else {
        $this->variable = $text;
        $this->value = true;
      }
    } else if(substr($text, 0, 1) == '-') {
      $this->variable = substr($text, 1, 0);
      $this->value = true;
      $this->type = Argument::FLAG;
    } else {
      $this->variable = $text;
      $this->value = null;
      $this->type = Argument::ARGUMENT;
    }
  }
  /**
   * Get the interpreted argument type
   * @return ArgumentType The interpreted ArgumentType of the current Argument
   */
  public function getType() : ArgumentType {
    return $this->type;
  }
  /**
   * Get the Argument's interpreted variable name
   * @return string The interpreted variable name
   */
  public function getVariable() : string {
    return $this->variable;
  }
  /**
   * Get the Argument's interpreted value
   * @return mixed The interpreved value
   */
  public function getValue() : mixed {
    return $this->value;
  }
}
