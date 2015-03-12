package cn.njnu.edu.bajdcc.lexer;

import java.util.ArrayList;
import java.util.List;

import cn.njnu.edu.bajdcc.lexer.algorithm.ITokenVisitor;
import cn.njnu.edu.bajdcc.lexer.algorithm.TokenAlgorithmCollection;

/**
 * �ʷ�������
 * 
 * @author bajdcc
 */
public class Lexer implements ITokenVisitor {
	/**
	 * ��������
	 */
	private ArrayList<Token> arrTokens = new ArrayList<Token>();

	/**
	 * ��ǰ����
	 */
	private Token curToken;

	/**
	 * Դ�ַ���
	 */
	private String strContext;

	/**
	 * �㷨���ϣ�DFA��ʽ��
	 */
	private TokenAlgorithmCollection algCollections;

	public Lexer(String strInput) {
		strContext = strInput;
		analysis();
	}

	/**
	 * @return ��������
	 */
	public List<Token> getTokens() {
		return arrTokens;
	}

	/**
	 * ���дʷ�����
	 */
	private void analysis() {

	}
}