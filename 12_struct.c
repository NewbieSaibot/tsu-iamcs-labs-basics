#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>

#define uint unsigned int
#define uchar unsigned int
#define file FILE
file *f;

typedef struct {
	wchar_t name[20], last_name[20], patronym[20];
	uint group;
	char grades[3];

	uchar grade_cnt[4];
	float avg;
} Student;

void GradeCalc(Student *student) {
	for (size_t i = 0; i < 3; i++) {
		student->grade_cnt[student->grades[i] - 2]++;
	}
	int tot = 0; for (size_t i = 0; i < 3; i++) tot += student->grade_cnt[i] * (i + 2);
	student->avg = (float)tot / 3;
}

void ReadStudent(Student* student) {
	wchar_t line[200] = { 0 };

	fgetws(line, sizeof(line), f);

	swscanf(line, L"%ls %ls %ls %u %hhu %hhu %hhu", student->last_name, student->name, student->patronym,
											&student->group, &student->grades[0], &student->grades[1],
											&student->grades[2], &student->grades[3]);

	GradeCalc(student);

	//wprintf(L"%ls\n", student->last_name);
}

Student *students;

int main() {
	setlocale(LC_ALL, "ru_RU.UTF-8");

	size_t n, k;
	scanf("%zu%zu", &n, &k);

	students = (Student*)malloc(sizeof(Student) * n);

	f = fopen("data.txt", "r+");

	if (f == NULL) {
		perror(":(");
		return 1;
	}

	for (int i = 0; i < n; i++) {
		ReadStudent(&students[i]);

		if (feof(f)) {
			n = i;
			wprintf(L"Переполнение студентами: %zu\n", n);
			break;
		}
	}

	fclose(f);

	Student best = (Student) {
		L"", L"Таких нет", L"",
		0,
		{0, 0, 0},

		{0, 0, 0, 0},
		0.f
	};
	
	for (int i = 0; i < n; i++) {
		if (students[i].group != k || students[i].grade_cnt[0]) {
			continue;
		}

		if (students[i].grade_cnt[3] > best.grade_cnt[3]) {
			memcpy(&best, &students[i], sizeof(best));
		}
	}

	wprintf(L"%ls\n", best.last_name);

	free(students);

	return 0;
}
