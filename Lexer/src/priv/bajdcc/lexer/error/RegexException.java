package priv.bajdcc.lexer.error;

/**
 * 正则表达式生成过程中的异常
 * 
 * @author bajdcc
 *
 */
public class RegexException extends Exception {

	/**
	 * 
	 */
	private static final long serialVersionUID = 51820185044284191L;

	/**
	 * 正则表达式解析过程中的错误
	 */
	public enum RegexError {
		NULL("正则表达式为空"),
		CTYPE("非法字符"),
		ESCAPE("非法的转义字符"),
		BRACK("中括号不匹配"),
		PAREN("小括号不匹配"),
		BRACE("大括号不匹配"),
		RANGE("范围不正确"),
		SYNTAX("语法错误"),
		INCOMPLETE("正则表达式不完整");

		private String message;

		RegexError(String message) {
			this.message = message;
		}

		public String getMessage() {
			return message;
		}

		public void setMessage(String message) {
			this.message = message;
		}
	};

	public RegexException(RegexError error, int location) {
		super(error.getMessage());
		m_iLocation = location;
		m_kError = error;
	}

	/**
	 * 位置
	 */
	private int m_iLocation = -1;

	/**
	 * @return 错误位置
	 */
	public int getLocation() {
		return m_iLocation;
	}

	/**
	 * 错误类型
	 */
	private RegexError m_kError = RegexError.NULL;

	/**
	 * @return 错误类型
	 */
	public RegexError getErrorCode() {
		return m_kError;
	}
}
