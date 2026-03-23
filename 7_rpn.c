#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char* binary_operands[] = {
	"+",
	"-",
	"*",
	"/",
	"`mod`",
	"^^",
	"`and`",
	"`or`",
	"`xor`",
	"`shl`",
	"`shr`",
	NULL
};

const char* unary_operands[] = {
	"`not`",
	"-",
	NULL
};

bool isbinaryoperand(const char* str) {
	for (size_t i = 0; binary_operands[i] != NULL; i++) {
		if (strcmp(binary_operands[i], str) == 0) {
			return true;
		}
	}
	return false;
}

bool isunaryoperand(const char* str) {
	for (size_t i = 0; unary_operands[i] != NULL; i++) {
		if (strcmp(unary_operands[i], str) == 0) {
			return true;
		}
	}
	return false;
}

int operand_priority(const char* str) {
	if (strcmp("`not`", str) == 0) {
		return 5;
	} else if (strcmp("`and`", str) == 0 || strcmp("`or`", str) == 0 
	|| strcmp("`xor`", str) == 0) {
		return 4;
	} else if (strcmp("^^", str) == 0) {
		return 3;
	} else if (strcmp("*", str) == 0 || strcmp("/", str) == 0 || strcmp("`mod`", str) == 0) {
		return 2;
	}
	return 1;
}

typedef enum {
	T_CLOSING,
	T_OPENING,
	T_CONST,
	T_VAR,
	T_OP_UNARY,
	T_OP_BINARY,
	T_EMPTY
} TokenType;

typedef struct {
	size_t size;
	size_t cap;
	TokenType type;
	char* str;
} Token;

typedef struct Node {
	struct Node* prev;
	Token* tok;
	int priority;
} Node;

#define isword(c) (isalnum(c) || c == '_')

size_t m = 0;
size_t cap = 4;

void reset_tokenizer() {
	m = 0;
	cap = 4;
}

Token* tokenize(const char* expr) {
	reset_tokenizer();
	
	Token* ret = (Token*)malloc(cap * sizeof(Token));

	if (ret == NULL || expr == NULL) {
		assert(0 && ":(");
	}

	int brackets = 0;

#define inc_token_array_size\
	if (m >= cap) { \
		cap *= 2; \
		ret = (Token*)realloc(ret, cap * sizeof(Token)); \
	}

	TokenType cur_tt = T_EMPTY, prev_tt = T_EMPTY;

	for (size_t i = 0; expr[i]; i++) {
		if (isspace(expr[i])) {
			continue;
		}
		else if (isword(expr[i])) {
			Token cur;
			cur.size = 0;
			cur.cap = 4;
			cur.str = (char*)malloc(sizeof(char) * cur.cap);
			
			if (isdigit(expr[i])) {
				cur.type = cur_tt = T_CONST;
			} else {
				cur.type = cur_tt = T_VAR;
			}

			while (isword(expr[i])) {
				if (cur.size >= cur.cap - 1) {
					cur.cap *= 2;
					cur.str = (char*)realloc(cur.str, cur.cap * sizeof(char));
				}

				if (cur.type == T_CONST && !isdigit(expr[i]) && expr[i] != '_') {
					assert(0 && "Invalid character in constant");
				}

				cur.str[cur.size++] = expr[i++];
			}
			cur.str[cur.size] = '\0';
			i--;

			inc_token_array_size;
			ret[m++] = cur;
		} 
		else if (expr[i] == ')') {
			brackets--;

			if (brackets < 0) {
				assert(0 && "Unbalanced bracket sequence.");
			}
			if (prev_tt == T_OP_BINARY || prev_tt == T_OP_UNARY || prev_tt == T_OPENING) {
				assert(0 && "Empty bracket or operand before closing bracket.");
			}

			inc_token_array_size;

			Token cur;
			cur.size = 1;
			cur.cap = 2;
			cur.str = (char*)malloc(sizeof(char) * cur.cap);
			cur.str[0] = ')';
			cur.str[1] = '\0';
			cur.type = cur_tt = T_CLOSING;

			ret[m++] = cur;
		}
		else if (expr[i] == '(') {
			brackets++;

			inc_token_array_size;

			Token cur;
			cur.size = 1;
			cur.cap = 2;
			cur.str = (char*)malloc(sizeof(char) * cur.cap);
			cur.str[0] = '(';
			cur.str[1] = '\0';
			cur.type = cur_tt = T_OPENING;

			if (prev_tt == T_CLOSING || prev_tt == T_CONST || prev_tt == T_VAR) {
				assert(0 && "Opening bracket after operand or closing bracket");
			}

			ret[m++] = cur;
		}
		else if (expr[i] == '`') {
			Token cur;
			cur.size = 0;
			cur.cap = 4;
			cur.str = (char*)malloc(sizeof(char) * cur.cap);
			
			cur.str[cur.size++] = expr[i++];

			bool complete = false;

			while (expr[i] && !complete) {
				if (cur.size >= cur.cap - 1) {
					cur.cap *= 2;
					cur.str = (char*)realloc(cur.str, cur.cap * sizeof(char));
				}

				cur.str[cur.size++] = expr[i];

				if (expr[i] == '`') {
					complete = true;
				}
				i++;
			}
			cur.str[cur.size] = '\0';

			if (!complete) {
				assert(0 && "Expected '`'.");
			}
			i--;

			if (strcmp(cur.str, "`and`") == 0 || strcmp(cur.str, "`or`") == 0 ||
				strcmp(cur.str, "`xor`") == 0 || strcmp(cur.str, "`mod`") == 0 ||
				strcmp(cur.str, "`shl`") == 0 || strcmp(cur.str, "`shr`") == 0) {
				cur.type = cur_tt = T_OP_BINARY;
			}
			else if (strcmp(cur.str, "`not`") == 0) {
				cur.type = cur_tt = T_OP_UNARY;
			}
			else {
				fprintf(stderr, "Unknown operator: %s\n", cur.str);
				assert(0 && "Unknown operator.");
			}

			inc_token_array_size;
			ret[m++] = cur;
		}
		else if (expr[i] == '*' || expr[i] == '/') {
			inc_token_array_size;

			Token cur;
			cur.size = 1;
			cur.cap = 2;
			cur.str = (char*)malloc(sizeof(char) * cur.cap);
			cur.str[0] = expr[i];
			cur.str[1] = '\0';
			
			cur.type = cur_tt = T_OP_BINARY;

			ret[m++] = cur;
		}
		else if (expr[i] == '^') {
			if (expr[i + 1] == '^') {
				Token cur;
				cur.size = 2;
				cur.cap = 3;
				cur.str = (char*)malloc(sizeof(char) * cur.cap);
				cur.str[0] = '^';
				cur.str[1] = '^';
				cur.str[2] = '\0';
				cur.type = cur_tt = T_OP_BINARY;
				
				inc_token_array_size;
				ret[m++] = cur;
				i++;
			} else {
				assert(0 && "Expected '^' after '^' to form '^^' operator.");
			}
		}
		else if (expr[i] == '+') {
			inc_token_array_size;

			Token cur;
			cur.size = 1;
			cur.cap = 2;
			cur.str = (char*)malloc(sizeof(char) * cur.cap);
			cur.str[0] = '+';
			cur.str[1] = '\0';
			
			cur.type = cur_tt = T_OP_BINARY;

			ret[m++] = cur;
		}
		else if (expr[i] == '-') {
			inc_token_array_size;

			Token cur;
			cur.size = 1;
			cur.cap = 2;
			cur.str = (char*)malloc(sizeof(char) * cur.cap);
			cur.str[0] = '-';
			cur.str[1] = '\0';
			
			if (prev_tt == T_EMPTY || prev_tt == T_OPENING || 
				prev_tt == T_OP_BINARY || prev_tt == T_OP_UNARY) {
				cur.type = cur_tt = T_OP_UNARY;
			} else {
				cur.type = cur_tt = T_OP_BINARY;
			}

			ret[m++] = cur;
		}
		else {
			fprintf(stderr, "Unexpected character: '%c' (ASCII %d)\n", expr[i], expr[i]);
			assert(0 && "Unexpected character.");
		}

		prev_tt = cur_tt;
	}

	if (brackets != 0) {
		assert(0 && "Unbalanced bracket sequence.");
	}
	if (prev_tt == T_OP_BINARY || prev_tt == T_OP_UNARY) {
		assert(0 && "Expected a variable or a const at the end.");
	}
	
	return ret;
}

void validate_token(Token* tok, size_t cnt) {
    for (size_t i = 0; i < cnt - 1; i++) {
		if (tok[i].type == T_OP_BINARY && tok[i + 1].type == T_OP_BINARY) {
			assert(0 && "Consecutive binary operands\n");
		} else if ((tok[i].type == T_CONST && tok[i + 1].type == T_VAR) ||
				(tok[i].type == T_VAR && tok[i + 1].type == T_CONST) ||
				(tok[i].type == T_VAR && tok[i + 1].type == T_VAR) ||
				(tok[i].type == T_CONST && tok[i + 1].type == T_CONST)) {
			assert(0 && "Consecutive numbers\n");
		} else if (i > 0
				&& ((tok[i - 1].type != T_CONST && tok[i - 1].type != T_VAR && tok[i - 1].type != T_CLOSING)
				&& (tok[i].type == T_OP_BINARY)
				&& (tok[i + 1].type != T_CONST && tok[i + 1].type != T_VAR != tok[i + 1].type != T_OPENING))) {
			assert(0 && "Binary operand must be sandwiched\n");
		} else if (tok[i].type == T_OP_UNARY && tok[i + 1].type == T_OP_BINARY) {
			assert(0 && "No binary operand after unary operand\n");
		}
    }

	if (tok[0].type == T_OP_BINARY) {
		assert(0 && "Binary operand must be sandwiched\n");
	}
}

Node* rpn_tok(Token* tok) {
	Node* output = NULL;
	Node* op_stack = NULL;

	if (tok == NULL) {
		assert(0 && ":(");
	}
	
	for (size_t i = 0; i < m; i++) {
		if (tok[i].type == T_OPENING) {
			Node* top = (Node*)malloc(sizeof(Node));
			top->prev = op_stack;
			top->tok = &tok[i];
			top->priority = 0;
			op_stack = top;
		} else if (tok[i].type == T_CLOSING) {
			while (op_stack != NULL && op_stack->tok->type != T_OPENING) {
				Node* tmp = op_stack;
				op_stack = op_stack->prev;
				
				tmp->prev = output;
				output = tmp;
			}
			
			if (op_stack == NULL || op_stack->tok->type != T_OPENING) {
				assert(0 && "Unbalanced bracket sequence.");
			}
			
			Node* tmp = op_stack;
			op_stack = op_stack->prev;
			free(tmp);
		} else if (tok[i].type == T_CONST || tok[i].type == T_VAR) {
			Node* top = (Node*)malloc(sizeof(Node));
			top->prev = output;
			top->tok = &tok[i];
			top->priority = 0;
			output = top;
		} else if (tok[i].type == T_OP_BINARY) {
			int priority = operand_priority(tok[i].str);
			
			while (op_stack != NULL && 
				   op_stack->tok->type != T_OPENING && 
				   op_stack->priority >= priority) {
				Node* tmp = op_stack;
				op_stack = op_stack->prev;
				
				tmp->prev = output;
				output = tmp;
			}
			
			Node* top = (Node*)malloc(sizeof(Node));
			top->prev = op_stack;
			top->tok = &tok[i];
			top->priority = priority;
			op_stack = top;
		} else if (tok[i].type == T_OP_UNARY) {
			Node* top = (Node*)malloc(sizeof(Node));
			top->prev = op_stack;
			top->tok = &tok[i];
			top->priority = 5;
			op_stack = top;
		} else {
			assert(0 && "Unknown token type.");
		}
	}
	
	while (op_stack != NULL) {
		if (op_stack->tok->type == T_OPENING) {
			assert(0 && "Unbalanced bracket sequence.");
		}
		Node* tmp = op_stack;
		op_stack = op_stack->prev;
		
		tmp->prev = output;
		output = tmp;
	}
	
	return output;
}

void print_rpn(Node* rpn) {
	Node* reversed = NULL;
	int cnt = 0;
	
	for (Node* p = rpn; p != NULL; p = p->prev) {
		cnt++;
	}

	char** tokens = (char**)malloc(cnt * sizeof(char*));
	int i = cnt - 1;
	
	for (Node* p = rpn; p != NULL; p = p->prev) {
		tokens[i--] = p->tok->str;
	}
	
	printf("RPN: ");
	for (int i = 0; i < cnt; i++) {
		printf("%s ", tokens[i]);
	}
	printf("\n");
	
	free(tokens);
}

int main(int argc, char** argv) {
	if (argc < 2) {
		fprintf(stderr, "No argument provided\n");
		return 1;
	}

	size_t alls = 0;
	for (size_t i = 1; i < argc; i++) {
		alls += strlen(argv[i]);
	}

	char* expr = (char*)malloc(sizeof(char) * (alls + 1));

	if (expr == NULL) {
		fprintf(stderr, "Invalid argument\n");
		return 1;
	}

	expr[0] = '\0';

	for (size_t i = 1; i < argc; i++) {
		printf("%s\n", argv[i]);
		strcat(expr, argv[i]);
	}
		
	printf("\n========================================\n");
	printf("Expression: %s\n", expr);
	printf("========================================\n");

	Token* t = tokenize(expr);

	printf("\nTokens:\n");
	for (size_t j = 0; j < m; j++) {
		printf("  Token %zu: type=%-7d str='%s'\n", 
			j, t[j].type, t[j].str);
	}

	validate_token(t, m);

	Node *rpn = rpn_tok(t);
	
	print_rpn(rpn);

	for (size_t j = 0; j < m; j++) {
		free(t[j].str);
	}
	free(t);
	
	while (rpn != NULL) {
		Node* tmp = rpn;
		rpn = rpn->prev;
		free(tmp);
	}

	free(expr);
	
	printf("\n");

	return 0;
}
