#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include <wchar.h>
#include <stdio.h>

using namespace std;

class m_string
{
private:
	wchar_t *p; // вказівник, тут зберігатимемо символьний рядок wchar_t бо юнікод (просто char це ASCII)
	int length; // довжина рядка щоб не рахувати кожний раз, а 1 раз тільки при заповненні
public:
	m_string() { p = nullptr; length = 0; } // конструктор що ініціалізує пустотою, щоб не було сміття (тобто скидає в нуль значення полів класу)
	m_string(wchar_t *wsInput)
	{ 
		length = wcslen(wsInput); // визначається довжина рядка в поле класу
		p = new wchar_t[length]; // виділяється пам'ять розміром з рядок, +1 символ не треба, бо нульсимвол стане на місці \n
		if (!this->p) // якщо не виділилась пам'ять вийти з програми
			exit(1); // аварійне завершення програми
		for (int i = 0; i < length; i++) // заповнення поля класу, переданим рядком в конструктор
			p[i] = wsInput[i]; // посимвольне присвоєння
		p[length-1] = '\0'; // ставим нульсимвол як завершення рядка
	}
	~m_string() { delete[] this->p; } // дектрустор для вивільнення пам'яті
	wchar_t *getString(void) { return this->p; } // функція для доступу до рядка *р в екземплярі класу
	void concatString(const m_string &str1, const m_string &str2) // фукнція конкатинації
	{
		if (this->p != nullptr) // перевіряємо чи наш this->p тобто поле класу не NULL
			delete[] p; // якщо ні то очищаємо стару пам'ять
		this->p = new wchar_t[str1.length + str2.length + 1]; // виділяємо нову на 2 рядочки які об'єднуємо
		int i = 0; // лічинльник для непреривного об'єднання
		for (; i < str1.length - 1; i++) // переписуємо 1 рядок в новий
			p[i] = str1.p[i]; // посимвольний перепис
		for (int j = 0; j < str2.length; j++, i++) // переписуємо 2 рядок продовжуючи за рахунок лічильника об'єднання
			p[i] = str2.p[j]; // посимвольний перепис 2 рядка
		p[str1.length + str2.length] = '\0'; // завершуєм присвоєнням нульсимвола в новий рядок
	}
	bool strString(wchar_t *wsInput) { return wcsstr(p, wsInput) != NULL ? true : false; } // функція визначення приналежності рядка (тобто чи є підрядком?)
};

int main()
{
	system("chcp 1251"); // підключаєм кирилицю в консоль
	wchar_t str1_buf[256]; // створюємо буфер ( рядок де тримаємо тимчасово те що ввели)
	cout << "Введіть перше речення чи слово: ";
	fgetws(str1_buf, 256, stdin); // заповнюємо буфер вводу із потоку вводу (консолі де вводимо) stdin
	m_string str(str1_buf); // ініціалізуємо при створенні об'єкт класу m_string із назвою str буфером вводу str_buf
	cout << "Введіть друге речення чи слово: ";
	fgetws(str1_buf, 256, stdin); // заповнюємо буфер вводу із потоку вводу (консолі де вводимо) stdin
	m_string str2(str1_buf);  // ініціалізуємо при створенні об'єкт класу m_string із назвою str2 буфером вводу str_buf
	printf("Входить рядок 2 в рядок 1: %s", str.strString(str2.getString()) == 1 ? "входить\n" : "ні\n"); // перевіряємо приналежність рядка із екземпляру класу str2 
	//до рядку екземпляру класу str1 
	m_string str3; // створюємо 3 екземпляр класу для конкатинації двох попередніх
	cout << "Результат конкатинації: "; 
	str3.concatString(str, str2); // конкатинуємо викликаючи функцію
	fputws(str3.getString(), stdout); // виводимо результат конкатинацї в потік виводу stdout (на консоль)
	cout << endl; // для наглядності переносимо все що напише віжуалка на новий рядок
	system("pause"); // зупиняємо консоль
	return 0; // повертаємо операційній системі 0 як сигнал про успішне завершення програми
}
