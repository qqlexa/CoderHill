#include <iostream>
#include <math.h>

using namespace std;

void print_arr(int** arr, int n, int m) {
	cout << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void print_vector(int* arr, int n) {
	cout << endl;
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

float find_det(int** arr, int n) {
	if (n == 2) {
		float det = (**arr * arr[1][1]) - (arr[0][1] * arr[1][0]);
		return det;
	}

	int sign;
	float det = 0;

	int** indirrect_arr = new int* [n - 1];
	for (int i = 0; i < n; i++) {
		*(indirrect_arr + i) = new int[n - 1];
	}

	float indirrect_det = 0;
	for (int element_i = 0, element_j = 0; element_j < n; element_j++) {
		for (int i2 = 0, i = 0; i2 < n; i2++) {
			if (i2 == element_i) continue;
			for (int j2 = 0, j = 0; j2 < n; j2++) {
				if (j2 == element_j) continue;
				indirrect_arr[i][j] = arr[i2][j2];
				j++;
			}
			i++;
		}

		indirrect_det = find_det(indirrect_arr, n - 1);
		sign = ((element_i + element_j) % 2) ? -1 : 1;
		det += float(sign * arr[element_i][element_j] * indirrect_det);
	}
	return det;
}

int** get_alg_matrix(int** arr, int n) {
	int** alg_arr = new int* [n];
	for (int i = 0; i < n; i++) {
		*(alg_arr + i) = new int[n];
	}

	if (n == 2) {
		alg_arr[0][0] = arr[1][1];
		alg_arr[0][1] = -arr[1][0];
		alg_arr[1][0] = -arr[0][1];
		alg_arr[1][1] = arr[0][0];
		return alg_arr;
	}


	int sign;

	int** indirrect_arr = new int* [n - 1];
	for (int i = 0; i < n; i++) {
		*(indirrect_arr + i) = new int[n - 1];
	}

	float indirrect_det = 0;
	for (int element_j = 0; element_j < n; element_j++) {
		for (int element_i = 0; element_i < n; element_i++) {
			for (int i2 = 0, i = 0; i2 < n; i2++) {
				if (i2 == element_i) continue;
				for (int j2 = 0, j = 0; j2 < n; j2++) {
					if (j2 == element_j) continue;
					indirrect_arr[i][j] = arr[i2][j2];
					j++;
				}
				i++;
			}

			indirrect_det = find_det(indirrect_arr, n - 1);
			sign = ((element_i + element_j) % 2) ? -1 : 1;
			alg_arr[element_i][element_j] = float(sign * indirrect_det);
		}
	}
	return alg_arr;
}

char translate_int_to_char(int number) {
	char symbol = char(65);
	if (number < 26) {
		symbol = char(number + 65);
	}
	else {
		switch (number) {
		case 26: {
			symbol = ' ';
			break;
		}
		case 27: {
			symbol = '!';
			break;
		}
		case 28: {
			symbol = ',';
			break;
		}
		case 29: {
			symbol = '-';
			break;
		}
		case 30: {
			symbol = '.';
			break;
		}

		}
	}
	return symbol;
}

int translate_char_to_int(char symbol) {
	int number = 0;


	switch (int(symbol)) {
	case 32: {
		number = 26;
		break;
	}
	case 33: {
		number = 27;
		break;
	}
	case 44: {
		number = 28;
		break;
	}
	case 45: {
		number = 29;
		break;
	}
	case 46: {
		number = 30;
		break;
	}
	default: {
		number = int(symbol) - 65;
		break;
	}
	}


	return number;
}

int** translate_key_to_matrix(string key) {
	int n = sqrt(key.length());
	int** arr = new int* [n];
	int x = 0;
	for (int i = 0; i < n; i++) {
		*(arr + i) = new int[n];
		for (int j = 0; j < n; j++) {
			arr[i][j] = translate_char_to_int(key[x]);
			x++;
		}
	}
	return arr;
}

string translate_matrix_to_key(int** arr, int n) {
	string key;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			key += translate_int_to_char(arr[i][j]);
		}
	}
	return key;
}

int* translate_cipher_to_vector(string cipher) {
	int n = cipher.length();

	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		*(arr + i) = translate_char_to_int(cipher[i]);
	}
	return arr;
}

string translate_vector_to_cipher(int* arr, int n) {
	string cipher;

	for (int i = 0; i < n; i++) {
		cipher += translate_int_to_char(arr[i]);
	}
	return cipher;
}

int* mod_vector(int* arr, int n, int alphabet_size) {
	for (int i = 0; i < n; i++) {
		*(arr + i) = *(arr + i) % alphabet_size;
		while (arr[i] < 0) arr[i] += alphabet_size;
	}
	return arr;
}

int** mod_matrix(int** arr, int n, int alphabet_size) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			*(*(arr + i) + j) = *(*(arr + i) + j) % alphabet_size;
			while (arr[i][j] < 0) arr[i][j] += alphabet_size;
		}
	}
	return arr;
}

int* multiply_matrix(int** arr, int* vector, int n) {
	int* final_vector = new int[n];
	for (int i = 0; i < n; i++) {
		*(final_vector + i) = 0;
	}


	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			*(final_vector + i) += float(arr[i][j] * vector[j]);
		}
	}
	return final_vector;
}


void gcdext(int a, int b, int* d, int* x, int* y) {
	int s;

	if (b == 0) {
		*d = a;
		*x = 1;
		*y = 0;

		return;
	}
	gcdext(b, a % b, d, x, y);
	s = *y;
	*y = *x - (a / b) * (*y);
	*x = s;

	return;
}


string code_hill(string message, string key, int alphabet_size) {
	string coded_message;
	int message_n;
	int key_n = key.length();
	int n = sqrt(key_n);
	int counter = 0;

	int* vector;
	string part_message;

	int** arr = translate_key_to_matrix(key);
	print_arr(arr, n, n);

	int* vector_result;

	while (message.length() % n != 0) {
		message += ' ';
	}
	message_n = message.length();

	for (int i = 0; i < message_n; i++) {
		part_message += message[i];
		counter++;
		if (counter < n) {
			continue;
		}
		vector = translate_cipher_to_vector(part_message);
		vector_result = multiply_matrix(arr, vector, n);

		vector_result = mod_vector(vector_result, n, alphabet_size);


		coded_message += translate_vector_to_cipher(vector_result, n);
		counter = 0;
		part_message = "";
	}
	cout << "From - " << message << ". Coded - " << coded_message << endl;
	return coded_message;
}


string decode_hill(string coded_message, string key, int alphabet_size) {
	int d, x, y;

	string message;
	int message_n = coded_message.length();
	int key_n = key.length();
	int n = sqrt(key_n);
	int counter = 0;

	int* vector;
	string part_message;
	int** arr = translate_key_to_matrix(key);
	cout << "BEGIN KEY" << endl;
	print_arr(arr, n, n);
	int det = find_det(arr, n);
	arr = get_alg_matrix(arr, n);
	cout << "Det is " << det << endl;

	arr = mod_matrix(arr, n, alphabet_size);


	gcdext(det, alphabet_size, &d, &x, &y);

	if (det < 0) {
		if (x > 0) {
			x = -x;
		}
	}

	while (x < 0) x += alphabet_size;


	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			arr[i][j] *= x;
		}
	}
	
	// T-matrix
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			swap(arr[i][j], arr[j][i]);
		}
	}

	arr = mod_matrix(arr, n, alphabet_size);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i][j] < 0) {
				arr[i][j] += alphabet_size;
			}
		}
	}
	cout << "Invertible matrix" << endl;
	print_arr(arr, n, n);

	int* vector_result;

	for (int i = 0; i < message_n; i++) {
		part_message += coded_message[i];
		counter++;
		if (counter < n) {
			continue;
		}
		vector = translate_cipher_to_vector(part_message);

		vector_result = multiply_matrix(arr, vector, n);

		vector_result = mod_vector(vector_result, n, alphabet_size);

		message += translate_vector_to_cipher(vector_result, n);
		counter = 0;
		part_message = "";
	}
	cout << "From - " << coded_message << ". Decoded - " << message << endl;
	return message;
}

int main() {
	// 31 	65 --> 90,	 0    1    2    3    4    5    6    7     8    9   10   11    12  13   14  15    16   17   18  19    20  21   22   23   24   25   26   27   28  29   30  |    32   33   44   45   46
	char alphabet[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};  //, ' ', '!', ',', '-', '.'};
	int alphabet_size = sizeof(alphabet) / sizeof(alphabet[0]);
	cout << "alphabet_size = " << alphabet_size << endl;
	string coded_message;
	string decoded_message;
	string key;
	string message;

	cout << "First " << endl;

	// first variant
	key = "CDBH";            // 2 3 1 7
	coded_message = "BHBZ";  // BHBZ

	decoded_message = decode_hill(coded_message, key, alphabet_size);
	cout << decoded_message << endl;

	cout << endl << endl;
	cout << "SECOND " << endl;
	
	// second variant
	
	key = "HICD";            // 7 8 2 3
	coded_message = "KBQB";  // KBQB

	decoded_message = decode_hill(coded_message, key, alphabet_size);
	cout << decoded_message << endl;

	// USE code_hill(decoded_message, key, alphabet_size) to check answer

	return 0;
}
