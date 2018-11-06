#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

int compare(char c_str[], int i, int j, int length, int cnt) {
	while (cnt < 3 && length - j - i >= 0) {
		if (c_str[i] != c_str[length - j]) { // �ݴ����� ���ڰ� �ٸ� ���
			if (length - j - i == 1) cnt++; // ���� �������� ���

			else if (c_str[i + 1] == c_str[length - j] && c_str[i] == c_str[length - j - 1]) { // ���� �� ���� ��� �� ��ġ�� ���
				if (compare(c_str, i + 1, j, length, cnt + 1) >= compare(c_str, i, j + 1, length, cnt + 1)) {
					j++, cnt++;
				}
				else if (compare(c_str, i + 1, j, length, cnt + 1) <= compare(c_str, i, j + 1, length, cnt + 1)) {
					i++, cnt++;
				}
			}
			else if (c_str[i + 1] == c_str[length - j]) { // ���� �����Ϳ��� �� ĭ ���� �Ͱ� ��ġ �� ���   ex)  TFTTTTF
				if (c_str[i] == c_str[length - j - 2]) {
					if(compare(c_str, i + 1, j, length, cnt + 1) >= compare(c_str, i, j + 2, length, cnt + 2)) {
						j += 2, cnt += 2;
					}
					else i++, cnt++;
				}
				else i++, cnt++;
			}
			else if (c_str[i] == c_str[length - j - 1]) { // ���� �����Ϳ��� �� ĭ ���� �Ͱ� ��ġ �� ���   ex)  FTTTTFT
				if (c_str[i + 2] == c_str[length - j]) {
					if (compare(c_str, i + 2, j, length, cnt + 2) <= compare(c_str, i, j + 1, length, cnt + 1)) {
						i += 2, cnt += 2;
					}
					else j++, cnt++;
				}
				else j++, cnt++;
			}
			else if (c_str[i + 1] == c_str[length - j - 1]) { // �� �� �տ� ���� ���   ex) TYFTTFXT
				cnt += 2, i++, j++;
			}

			else { // �� ĭ �̻��� ���
				if (c_str[i + 2] == c_str[length - j] && c_str[i] == c_str[length - j - 2]) { // ���� �� ���� ��� �� ��ġ�� ���
					if (compare(c_str, i + 2, j, length, cnt + 2) >= compare(c_str, i, j + 2, length, cnt + 2)) { 
						j += 2, cnt += 2;
					}
					else if (compare(c_str, i + 2, j, length, cnt + 2) <= compare(c_str, i, j + 2, length, cnt + 2)) {
						i += 2, cnt += 2;
					}
				}
				else if (c_str[i + 2] == c_str[length - j]) { // ���� �����Ϳ��� �� ĭ ���� �Ͱ� ��ġ �� ���
					i += 2, cnt += 2;
				}
				else if (c_str[i] == c_str[length - j - 2]) { // ���� �����Ϳ��� �� ĭ ���� �Ͱ� ��ġ �� ��� 
					j += 2, cnt += 2;
				}
				else { // �� ĭ �̻��� ���
					cnt += 3;
				}
			}
		}
		i++, j++;
	}
	return cnt;
}

int compare_Base(FILE *inp) {
	char c_str[1010]; // ���ڿ� ����
	fscanf(inp, "%s", &c_str);
	int length, cnt = 0;
	int i = 0, j = 0;
	length = strlen(c_str); 
	length--;
	
	if (compare(c_str, i, j, length, cnt) >= 3) return -1;
	else return compare(c_str, i, j, length, cnt);
}

int main() {
	FILE *inp = fopen("palindrome.inp", "r");
	FILE *out = fopen("palindrome.out", "w");

	int testCase;
	fscanf(inp, "%d", &testCase);

	for (int i = 0; i < testCase; i++) 	fprintf(out, "%d\n", compare_Base(inp));
	
	fclose(inp);
	fclose(out);
	return 0;
}
