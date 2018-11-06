#include<stdio.h>
#pragma warning(disable:4996)

int main() {
	FILE *inp = fopen("pandora.inp", "r");
	FILE *out = fopen("pandora.out", "w");
	int testcase;
	char S[100002];
	fscanf(inp,"%d\n", &testcase);
	for (; testcase > 0; testcase--) {
		fscanf(inp, "%s", &S);
		int i = 0, state = 3; // left = 0, down = 1, right = 2, up = 3
		int width_visible = 1, height_visible = 1;
		while (1) {
			if (S[i] == 'L') state = (state + 1) % 4;
			else if (S[i] == 'R') {
				state = (state + 3) % 4;
				if (i > 0) {
					if (S[i - 1] == 'R') {
						if (state == 1 || state == 3) width_visible = 0;
						if (state == 0 || state == 2) height_visible = 0;
					}
				}
			}
			else {
				if (S[i - 1] == 'R') {
					if (S[0] == 'R') {
						state = (state + 3) % 4;
						if (state == 1 || state == 3) width_visible = 0;
						if (state == 0 || state == 2) height_visible = 0;
					}
				}
				break;
			}
			i++;
		}
		fprintf(out, "%d\n", width_visible + height_visible);
	}
	fclose(inp);
	fclose(out);
	return 0;
}