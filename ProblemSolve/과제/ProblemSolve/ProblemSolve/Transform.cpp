#include<iostream>
#include<fstream>
#include<string>

using namespace std;

int seq, cnt, stack[1000], top, idx;
int arr[1000];

void toInt(string data) {
	while (seq--) {
		if (data[seq] == '(') { // 왼쪽 괄호면 스택에서 pop
			top--;
			arr[stack[top]] = cnt;
			cnt--;
		}
		else { // 오른쪽 괄호면 스택으로 push
			stack[top] = idx;
			idx--, top++;
		}
	}
}

string toString(int left, int right) {
	for (int i = left; i < right; i++) {
		if (arr[i] == seq) {
			seq++; // 다음 순서로 올려줌
			string str = "(" + toString(left, i) + ")"; // 왼쪽 노드인 경우 괄호 사이에 넣고
			str += toString(i + 1, right); // 오른쪽 노드인 경우 괄호 오른쪽에 추가
			return str;
		}
	}
	return "";
}

int main() {
	ifstream inp("Transform.inp");
	ofstream out("Transform.out");
	int testcase;
	inp >> testcase;
	while (testcase--) {
		int num, type;
		inp >> num >> type;
		out << num << " "; // 출력 포맷을 맞추기 위해 미리 출력.
		string str;
		
		if (type) { // type이 1인 경우 -> 문자열이 입력 데이터로 주어짐.
			seq = (num * 2); // 뒤쪽부터 순서대로
			cnt = num, top = 0, idx = num - 1;
			inp >> str; // 문자열 입력 받음.
			toInt(str);
			for (int i = 0; i < num; i++) out << arr[i] << " ";	// 출력
		} else { // type이 0인 경우 -> 숫자 배열이 입력 데이터로 주어짐.
			seq = 1; // 우선 첫번째 순서는 1
			for (int i = 0; i < num; i++) inp >> arr[i]; // 배열 입력 받음.
			str = toString(0, num); // 스트링으로 변환
			for (int i = 0; i < str.length(); i++) out << str[i]; // 출력
		}
		out << '\n';
	}
	inp.close();
	out.close();
	return 0;
}