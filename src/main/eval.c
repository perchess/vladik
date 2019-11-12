#include "mcu_support_package/inc/stm32f10x.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "eval.h"

int32_t convert(const char * string, int32_t * pointer)
{

		int32_t symbolCounter = 0; //считает кол-во символов в числе
		int32_t spaceCounter = 0; //считает кол-во пробелов в записи числа и знак после него
		//берётся значение из cursor, и выполняется цикл, пока не встретится арифметический знак, правая скобка
		//или конец строки
		for ( int32_t i = *pointer; !(*(string+i) == '\0' || *(string+i) == '+' || *(string+i) == '-'
				|| *(string+i) == '*' || *(string+i) == '/' || *(string+i) == ')' ) ; i++)
		{
			if (*(string+i) == ' ')
			{
				spaceCounter++;
			}
			else
			{
				symbolCounter++; //считаем кол-во символов в слагаемом
			}
		}



		char num_char[symbolCounter]; //создаём массив под число
		int32_t j = 0; //индекс массива



		//заполняем массив символами
		for ( int32_t i = *pointer; !(*(string+i) == '\0' || *(string+i) == '+' || *(string+i) == '-'
						|| *(string+i) == '*' || *(string+i) == '/' || *(string+i) == ')' ) ; i++)
		{
			if (*(string+i) != ' ')  //если символ не пробел, то вписываем его в массив
			{
				num_char[j] = *(string+i);
				j++;
			}
		}
		*pointer += symbolCounter + spaceCounter; //присваиваем курсору новое значение
		return atol(num_char); //переводим массив символов в число типа int32_t и возвращаем значение функции
}


int64_t convert_64 (const char * string, int64_t * pointer)
{
		int64_t symbolCounter = 0; //считает кол-во символов в числе
		int64_t spaceCounter = 0; //считает кол-во пробелов в записи числа и знак после него
		//берётся значение из cursor, и выполняется цикл, пока не встретится арифметический знак, правая скобка
		//или конец строки
		for ( int64_t i = *pointer; !(*(string+i) == '\0' || *(string+i) == '+' || *(string+i) == '-'
				|| *(string+i) == '*' || *(string+i) == '/' || *(string+i) == ')' ) ; i++)
		{
			if (*(string+i) == ' ')
			{
				spaceCounter++;
			}
			else
			{
				symbolCounter++; //считаем кол-во символов в слагаемом
			}
		}



		char num_char[symbolCounter]; //создаём массив под число
		int64_t j = 0; //индекс массива



		//заполняем массив символами
		for ( int64_t i = *pointer; !(*(string+i) == '\0' || *(string+i) == '+' || *(string+i) == '-'
						|| *(string+i) == '*' || *(string+i) == '/' || *(string+i) == ')' ) ; i++)
		{
			if (*(string+i) != ' ')  //если символ не пробел, то вписываем его в массив
			{
				num_char[j] = *(string+i);
				j++;
			}
		}
		*pointer += symbolCounter + spaceCounter; //присваиваем курсору новое значение
		return atoll(num_char); //переводим массив символов в число типа int64_t и возвращаем значение функции
}
	
	
float convert_float (const char * string, int * pointer)
{
		int symbolCounter = 0; //считает кол-во символов в числе
		int spaceCounter = 0; //считает кол-во пробелов в записи числа и знак после него
		//берётся значение из cursor, и выполняется цикл, пока не встретится арифметический знак, правая скобка
		//или конец строки
		for ( int i = *pointer; !(*(string+i) == '\0' || *(string+i) == '+' || *(string+i) == '-'
				|| *(string+i) == '*' || *(string+i) == '/' || *(string+i) == ')' ) ; i++)
		{
			if (*(string+i) == ' ')
			{
				spaceCounter++;
			}
			else
			{
				symbolCounter++; //считаем кол-во символов в слагаемом
			}
		}



		char num_char[symbolCounter]; //создаём массив под число
		int j = 0; //индекс массива



		//заполняем массив символами
		for ( int i = *pointer; !(*(string+i) == '\0' || *(string+i) == '+' || *(string+i) == '-'
						|| *(string+i) == '*' || *(string+i) == '/' || *(string+i) == ')' ) ; i++)
		{
			if (*(string+i) != ' ')  //если символ не пробел, то вписываем его в массив
			{
				num_char[j] = *(string+i);
				j++;
			}
		}
		*pointer += symbolCounter + spaceCounter; //присваиваем курсору новое значение
		return atof(num_char); //переводим массив символов в число типа float и возвращаем значение функции	
}
int32_t eval( const char * formula )
{
#warning Implement this!
	
	
		int32_t cursor = 0;
		int32_t *pointer = &cursor;
		int32_t total = 0; //итог
		int32_t bracketCounter = 0; //считает кол-во левых скобок
		int32_t stringLength = 0; //длина строки

		//считаем кол-во левых скобок и длину строки
		for (int32_t i = 0; *(formula+i) != '\0'; i++)
		{
			if (*(formula+i) == '(')
			{
				bracketCounter++;
			}
			stringLength++;
		}

    //создаём массив переключателей для каждого символа в строке: если переключатель равен 0,
		//то символ ещё не участвовал в вычислениях, а после участия переключатель становится равен 1
		bool selector [stringLength];
		//заполняем массив нулями
		memset(selector, 0, stringLength * sizeof(bool));

		//создаём массив для левых скобок
		int32_t bracketPosition[bracketCounter];
		
		//создаём массив для хранения значений в скобках
		int32_t bracketValue[bracketCounter];
		
		//создаём массив для хранения кол-ва знаков в скобках, заполняем нулями
		int32_t signsInBracket[bracketCounter];
		memset(signsInBracket, 0, sizeof(int32_t));


		int32_t j = 0; //счётчик для массива скобок

		//сканируем строку и заносим в массив скобок их позиции
		for (int32_t i = 0; *(formula+i) != '\0'; i++)
		{
			if (*(formula+i) == '(')
			{
				bracketPosition[j] = i;

				j++;
			}
		}


		//рассматриваем содержимое скобок, начиная с самых последних
		for (int32_t k = sizeof(bracketPosition) / sizeof(bracketPosition[0]) - 1; k >= 0; k--)
		{
			*pointer = bracketPosition[k] + 1; //устанавливаем курсор на скобку, прибавляем 1, чтобы перепрыгнуть скобку
		
			int32_t counter;

			//считаем кол-во арифметических знаков внутри k-тых скобок для создания массива для чисел из k-тых скобок
			//цикл выполняется, пока не встретится правая скобка, которая ни разу не использовалась ранее
			for (counter = *pointer; !(*(formula + counter) == ')' && selector [counter] == 0); counter++)
			{
				//если знак появляется впервые, он учитывается
				if (selector [counter] == 0  &&  ( *(formula + counter) == '+' || *(formula + counter) == '-'
						|| *(formula + counter) == '*' || *(formula + counter) == '/') )
				{
					signsInBracket[k]++;
				}
			}

			for (int32_t i = bracketPosition[k]; i <= counter; i++)
			{
				selector [i] = 1;
			}
		
		}

		//обратно обнуляем все переключатели для дальнейшей работы
		for (int32_t i = 0; *(formula + i) != '\0'; i++)
		{
			selector [i] = 0;
		}



		//в этом цикле производится вычисление значений во всех скобках, начиная с последней
		for (int32_t k = sizeof(bracketPosition) / sizeof(bracketPosition[0]) - 1; k >= 0; k--)
		{
			int32_t num[signsInBracket[k] + 1]; //в этот массив будем заносить все значения чисел и скобок подряд
			int32_t index = 0;
			int32_t bracketIndex = k;
			bool isMinusTheFirst = 0; //проверяем, стоит ли минус перед первым значением в k-тых скобках
			int32_t counter = bracketPosition[k] + 1; //устанавливаем курсор на скобку, прибавляем 1, чтобы перепрыгнуть скобку

			//цикл выполняется, пока не встретится правая скобка, которая ни разу не использовалась ранее
			//то есть рассматривается область внутри k-тых скобок
			while ( ! ( *(formula + counter) == ')' && selector [counter] == 0 ) )
			{
				//если символ - пробел
				if ( *(formula + counter) == ' ' )
				{
					counter++;
				}

				//если натыкаемся на левую скобку
				else if ( *(formula + counter) == '(' )
				{
					bracketIndex++;
					//необходимо учитывать только первый "слой" скобок, поскольку все остальные уже учтены внутри него
					if (selector [ counter - 1 ] == 0)
					{
						num[index] = bracketValue[bracketIndex];
						index++;
						counter++;
					}
					//если скобки уже учтены ранее, selector == 1, и мы их просто пропускаем
					else
					{
						counter++;
					}
				}

				//иначе если встречаем минус впервые и раньше всех значений в k-тых скобках
				else if (selector [counter] == 0  &&  index == 0  &&  ( *(formula + counter) == '-' ) )
				{
					isMinusTheFirst = 1;
					counter++;
				}

				//иначе если символ встречается впервые и не является арифметическим знаком, переводим все символы,
				//начиная с него, в число при помощи функции convert, выполнение которой прекращается при встрече
				//арифметического знака или правой скобки
				else if ( selector [ counter ] == 0  &&  ( *(formula + counter) != '+' )  &&  ( *(formula + counter) != '-' )
						&&  ( *(formula + counter) != '*' )  &&  ( *(formula + counter) != '/' ) )
				{
					*pointer = counter;
					num[index] = convert (formula, pointer); //в ходе выполнения convert произойдёт перенос курсора
					counter = *pointer;
					index++;
				}

				//иначе, если символы уже были использованы и учтены ранее, т.е. seletor [*pointer] == 1 или если встретится
				//арифметический знак или правая скобка, то переходим к рассмотрению следующего символа
				else
				{
					counter++;
				}
			}


			//получили массив чисел num, в котором по порядку записаны все числа, участвующие в вычислениях в k-тых скобках



			counter = bracketPosition[k] + 1; //устанавливаем курсор в первоначальное положение
			int32_t sign; //считает знаки
			//если минус не стоит первым, то
			if (isMinusTheFirst == 0)
			{
				sign = 1;
				bracketValue[k] = num[0]; //предварительно присваиваем скобке значение первого участвующего в вычислениях числа
			}
			//иначе присваиваем скобке ноль, чтобы вычесть из него первое число
			else
			{
				sign = 0;
				bracketValue[k] = 0;
			}


			//теперь заново запускаем цикл while, идём слева направо и как только обнаруживаем знак, берём значения слева
			//и справа от него и производим вычисление

			//цикл выполняется, пока не встретится правая скобка, которая ни разу не использовалась ранее
			//то есть рассматривается область внутри k-тых скобок
			while ( ! ( *(formula + counter) == ')' && selector [counter] == 0 ) )
			{
				if (selector [counter] == 0)
				{
					switch ( *(formula + counter) )
					{
					case '+':
						bracketValue[k] = bracketValue[k] + num[sign];
						sign++;
						break;

					case '-':
						bracketValue[k] = bracketValue[k] - num[sign];
						sign++;
						break;

					case '*':
						bracketValue[k] = bracketValue[k] * num[sign];
						sign++;
						break;

					case '/':
						bracketValue[k] = bracketValue[k] / num[sign];
						sign++;
						break;

					default:
						break;
					}
				}

				counter++;
			}

			//таким образом, из цикла мы выйдем при указателе на правую скобку k-тых скобок


			//выставляем переключатель всех символов в k-тых скобках равным 1
			for (int32_t i = bracketPosition[k]; i <= counter; i++)
			{
				selector [i] = 1;
			}
		}




		//теперь возвращаемся в самое начало строки и рассматриваем её всю целиком

		int32_t signsInString = 0; //счётчик неучтенных знаков в строке целиком

		for (int32_t i = 0; *(formula + i) != '\0'; i++)
		{
			//если знак появляется впервые, он учитывается
			if (selector [i] == 0  &&  ( *(formula + i) == '+' || *(formula + i) == '-' || *(formula + i) == '*'
					|| *(formula + i) == '/'))
			{
				signsInString++;
			}
		}


		int32_t num[signsInString + 1]; //в этот массив будем заносить все значения чисел и скобок подряд
		int32_t index = 0;
		int32_t bracketIndex = -1; //т.к. самая первая скобка в строке имеет индекс 0
		bool isMinusTheFirst = 0; //проверяем, стоит ли минус перед первым значением в k-тых скобках
		int32_t counter = 0;

		while (*(formula + counter) != '\0')
		{
			//если символ - пробел
			if ( *(formula + counter) == ' ' )
			{
				counter++;
			}

			//если натыкаемся на левую скобку
			else if ( *(formula + counter) == '(' )
			{
				bracketIndex++;
				//необходимо учитывать только первый "слой" скобок, поскольку все остальные уже учтены внутри него
				if (selector [ counter - 1 ] == 0 || counter == 0)
				{
					num[index] = bracketValue[bracketIndex];
					index++;
					counter++;
				}
				else
				{
					counter++;
				}
			}

			//иначе если встречаем минус впервые и раньше всех значений в k-тых скобках
			else if (selector [ counter ] == 0  &&  index == 0  &&  ( *(formula + counter) == '-' ) )
			{
				isMinusTheFirst = 1;
				counter++;
			}

			//иначе если символ встречается впервые и не является арифметическим знаком, переводим все символы,
			//начиная с него, в число при помощи функции convert, выполнение которой прекращается при встрече
			//арифметического знака или правой скобки
			else if ( selector [ counter ] == 0  &&  ( *(formula + counter) != '+' )  &&  ( *(formula + counter) != '-' )
					&&  ( *(formula + counter) != '*' )  &&  ( *(formula + counter) != '/' ) )
			{
				*pointer = counter;
				num[index] = convert (formula, pointer); //в ходе выполнения convert произойдёт перенос курсора
				index++;
				counter = *pointer;
			}
			else
			{
				counter++;
			}
		}

		//получили массив чисел num, в котором по порядку записаны все числа, участвующие в вычислениях в k-тых скобках

		counter = 0; //устанавливаем курсор в первоначальное положение
		int32_t sign; //считает знаки
		//если минус не стоит первым, то
		if (isMinusTheFirst == 0)
		{
			sign = 1;
			total = num[0]; //предварительно присваиваем строке значение первого участвующего в вычислениях числа
		}
		//если минус первый, то присваиваем строке ноль, чтобы вычесть из него первое число
		else
		{
			sign = 0;
			total = 0;
		}

		//теперь запускаем цикл for, идём слева направо и как только обнаруживаем знак, берём значения слева
		//и справа от него и производим вычисление

		//цикл выполняется, пока не встретится правая скобка, которая ни разу не использовалась ранее
		//то есть рассматривается область внутри k-тых скобок
		for (counter = 0; *(formula + counter) != '\0'; counter++)
		{
			if (selector [counter] == 0)
			{
				switch ( *(formula + counter) )
				{
				case '+':
					total = total + num[sign];
					sign++;
					break;

				case '-':
					total = total - num[sign];
					sign++;
					break;

				case '*':
					total = total * num[sign];
					sign++;
					break;

				case '/':
					total = total / num[sign];
					sign++;
					break;

				default:
					break;
				}
			}
		}

	return total;
}





int64_t eval_64( const char * formula )
{
#warning Implement this!

		int64_t cursor = 0;
		int64_t *pointer = &cursor;
		int64_t total = 0; //итог
		int64_t bracketCounter = 0; //считает кол-во левых скобок
		int64_t stringLength = 0; //длина строки

		//считаем кол-во левых скобок и длину строки
		for (int64_t i = 0; *(formula+i) != '\0'; i++)
		{
			if (*(formula+i) == '(')
			{
				bracketCounter++;
			}
			stringLength++;
		}

    //создаём массив переключателей для каждого символа в строке: если переключатель равен 0,
		//то символ ещё не участвовал в вычислениях, а после участия переключатель становится равен 1
		bool selector [stringLength];
		//заполняем массив нулями
		memset(selector, 0, stringLength * sizeof(bool));

		//создаём массив для левых скобок
		int64_t bracketPosition[bracketCounter];
		
		//создаём массив для хранения значений в скобках
		int64_t bracketValue[bracketCounter];
		
		//создаём массив для хранения кол-ва знаков в скобках, заполняем нулями
		int64_t signsInBracket[bracketCounter];
		memset(signsInBracket, 0, sizeof(int64_t));


		int64_t j = 0; //счётчик для массива скобок

		//сканируем строку и заносим в массив скобок их позиции
		for (int64_t i = 0; *(formula+i) != '\0'; i++)
		{
			if (*(formula+i) == '(')
			{
				bracketPosition[j] = i;

				j++;
			}
		}


		//рассматриваем содержимое скобок, начиная с самых последних
		for (int64_t k = sizeof(bracketPosition) / sizeof(bracketPosition[0]) - 1; k >= 0; k--)
		{
			*pointer = bracketPosition[k] + 1; //устанавливаем курсор на скобку, прибавляем 1, чтобы перепрыгнуть скобку
		
			int64_t counter;

			//считаем кол-во арифметических знаков внутри k-тых скобок для создания массива для чисел из k-тых скобок
			//цикл выполняется, пока не встретится правая скобка, которая ни разу не использовалась ранее
			for (counter = *pointer; !(*(formula + counter) == ')' && selector [counter] == 0); counter++)
			{
				//если знак появляется впервые, он учитывается
				if (selector [counter] == 0  &&  ( *(formula + counter) == '+' || *(formula + counter) == '-'
						|| *(formula + counter) == '*' || *(formula + counter) == '/') )
				{
					signsInBracket[k]++;
				}
			}

			for (int64_t i = bracketPosition[k]; i <= counter; i++)
			{
				selector [i] = 1;
			}
		
		}

		//обратно обнуляем все переключатели для дальнейшей работы
		for (int64_t i = 0; *(formula + i) != '\0'; i++)
		{
			selector [i] = 0;
		}



		//в этом цикле производится вычисление значений во всех скобках, начиная с последней
		for (int64_t k = sizeof(bracketPosition) / sizeof(bracketPosition[0]) - 1; k >= 0; k--)
		{
			int64_t num[signsInBracket[k] + 1]; //в этот массив будем заносить все значения чисел и скобок подряд
			int64_t index = 0;
			int64_t bracketIndex = k;
			bool isMinusTheFirst = 0; //проверяем, стоит ли минус перед первым значением в k-тых скобках
			int64_t counter = bracketPosition[k] + 1; //устанавливаем курсор на скобку, прибавляем 1, чтобы перепрыгнуть скобку

			//цикл выполняется, пока не встретится правая скобка, которая ни разу не использовалась ранее
			//то есть рассматривается область внутри k-тых скобок
			while ( ! ( *(formula + counter) == ')' && selector [counter] == 0 ) )
			{
				//если символ - пробел
				if ( *(formula + counter) == ' ' )
				{
					counter++;
				}

				//если натыкаемся на левую скобку
				else if ( *(formula + counter) == '(' )
				{
					bracketIndex++;
					//необходимо учитывать только первый "слой" скобок, поскольку все остальные уже учтены внутри него
					if (selector [ counter - 1 ] == 0)
					{
						num[index] = bracketValue[bracketIndex];
						index++;
						counter++;
					}
					//если скобки уже учтены ранее, selector == 1, и мы их просто пропускаем
					else
					{
						counter++;
					}
				}

				//иначе если встречаем минус впервые и раньше всех значений в k-тых скобках
				else if (selector [counter] == 0  &&  index == 0  &&  ( *(formula + counter) == '-' ) )
				{
					isMinusTheFirst = 1;
					counter++;
				}

				//иначе если символ встречается впервые и не является арифметическим знаком, переводим все символы,
				//начиная с него, в число при помощи функции convert_64, выполнение которой прекращается при встрече
				//арифметического знака или правой скобки
				else if ( selector [ counter ] == 0  &&  ( *(formula + counter) != '+' )  &&  ( *(formula + counter) != '-' )
						&&  ( *(formula + counter) != '*' )  &&  ( *(formula + counter) != '/' ) )
				{
					*pointer = counter;
					num[index] = convert_64 (formula, pointer); //в ходе выполнения convert_64 произойдёт перенос курсора
					counter = *pointer;
					index++;
				}

				//иначе, если символы уже были использованы и учтены ранее, т.е. seletor [*pointer] == 1 или если встретится
				//арифметический знак или правая скобка, то переходим к рассмотрению следующего символа
				else
				{
					counter++;
				}
			}


			//получили массив чисел num, в котором по порядку записаны все числа, участвующие в вычислениях в k-тых скобках



			counter = bracketPosition[k] + 1; //устанавливаем курсор в первоначальное положение
			int64_t sign; //считает знаки
			//если минус не стоит первым, то
			if (isMinusTheFirst == 0)
			{
				sign = 1;
				bracketValue[k] = num[0]; //предварительно присваиваем скобке значение первого участвующего в вычислениях числа
			}
			//иначе присваиваем скобке ноль, чтобы вычесть из него первое число
			else
			{
				sign = 0;
				bracketValue[k] = 0;
			}


			//теперь заново запускаем цикл while, идём слева направо и как только обнаруживаем знак, берём значения слева
			//и справа от него и производим вычисление

			//цикл выполняется, пока не встретится правая скобка, которая ни разу не использовалась ранее
			//то есть рассматривается область внутри k-тых скобок
			while ( ! ( *(formula + counter) == ')' && selector [counter] == 0 ) )
			{
				if (selector [counter] == 0)
				{
					switch ( *(formula + counter) )
					{
					case '+':
						bracketValue[k] = bracketValue[k] + num[sign];
						sign++;
						break;

					case '-':
						bracketValue[k] = bracketValue[k] - num[sign];
						sign++;
						break;

					case '*':
						bracketValue[k] = bracketValue[k] * num[sign];
						sign++;
						break;

					case '/':
						bracketValue[k] = bracketValue[k] / num[sign];
						sign++;
						break;

					default:
						break;
					}
				}

				counter++;
			}

			//таким образом, из цикла мы выйдем при указателе на правую скобку k-тых скобок


			//выставляем переключатель всех символов в k-тых скобках равным 1
			for (int64_t i = bracketPosition[k]; i <= counter; i++)
			{
				selector [i] = 1;
			}
		}




		//теперь возвращаемся в самое начало строки и рассматриваем её всю целиком

		int64_t signsInString = 0; //счётчик неучтенных знаков в строке целиком

		for (int64_t i = 0; *(formula + i) != '\0'; i++)
		{
			//если знак появляется впервые, он учитывается
			if (selector [i] == 0  &&  ( *(formula + i) == '+' || *(formula + i) == '-' || *(formula + i) == '*'
					|| *(formula + i) == '/'))
			{
				signsInString++;
			}
		}


		int64_t num[signsInString + 1]; //в этот массив будем заносить все значения чисел и скобок подряд
		int64_t index = 0;
		int64_t bracketIndex = -1; //т.к. самая первая скобка в строке имеет индекс 0
		bool isMinusTheFirst = 0; //проверяем, стоит ли минус перед первым значением в k-тых скобках
		int64_t counter = 0;

		while (*(formula + counter) != '\0')
		{
			//если символ - пробел
			if ( *(formula + counter) == ' ' )
			{
				counter++;
			}

			//если натыкаемся на левую скобку
			else if ( *(formula + counter) == '(' )
			{
				bracketIndex++;
				//необходимо учитывать только первый "слой" скобок, поскольку все остальные уже учтены внутри него
				if (selector [ counter - 1 ] == 0 || counter == 0)
				{
					num[index] = bracketValue[bracketIndex];
					index++;
					counter++;
				}
				else
				{
					counter++;
				}
			}

			//иначе если встречаем минус впервые и раньше всех значений в k-тых скобках
			else if (selector [ counter ] == 0  &&  index == 0  &&  ( *(formula + counter) == '-' ) )
			{
				isMinusTheFirst = 1;
				counter++;
			}

			//иначе если символ встречается впервые и не является арифметическим знаком, переводим все символы,
			//начиная с него, в число при помощи функции convert_64, выполнение которой прекращается при встрече
			//арифметического знака или правой скобки
			else if ( selector [ counter ] == 0  &&  ( *(formula + counter) != '+' )  &&  ( *(formula + counter) != '-' )
					&&  ( *(formula + counter) != '*' )  &&  ( *(formula + counter) != '/' ) )
			{
				*pointer = counter;
				num[index] = convert_64 (formula, pointer); //в ходе выполнения convert_64 произойдёт перенос курсора
				index++;
				counter = *pointer;
			}
			else
			{
				counter++;
			}
		}

		//получили массив чисел num, в котором по порядку записаны все числа, участвующие в вычислениях в k-тых скобках

		counter = 0; //устанавливаем курсор в первоначальное положение
		int64_t sign; //считает знаки
		//если минус не стоит первым, то
		if (isMinusTheFirst == 0)
		{
			sign = 1;
			total = num[0]; //предварительно присваиваем строке значение первого участвующего в вычислениях числа
		}
		//если минус первый, то присваиваем строке ноль, чтобы вычесть из него первое число
		else
		{
			sign = 0;
			total = 0;
		}

		//теперь запускаем цикл for, идём слева направо и как только обнаруживаем знак, берём значения слева
		//и справа от него и производим вычисление

		//цикл выполняется, пока не встретится правая скобка, которая ни разу не использовалась ранее
		//то есть рассматривается область внутри k-тых скобок
		for (counter = 0; *(formula + counter) != '\0'; counter++)
		{
			if (selector [counter] == 0)
			{
				switch ( *(formula + counter) )
				{
				case '+':
					total = total + num[sign];
					sign++;
					break;

				case '-':
					total = total - num[sign];
					sign++;
					break;

				case '*':
					total = total * num[sign];
					sign++;
					break;

				case '/':
					total = total / num[sign];
					sign++;
					break;

				default:
					break;
				}
			}
		}

	return total;
}



float eval_float( const char * formula )
{
#warning Implement this!
		int cursor = 0;
		int *pointer = &cursor;
		float total = 0; //итог
		int bracketCounter = 0; //считает кол-во левых скобок
		int stringLength = 0; //длина строки

		//считаем кол-во левых скобок и длину строки
		for (int i = 0; *(formula+i) != '\0'; i++)
		{
			if (*(formula+i) == '(')
			{
				bracketCounter++;
			}
			stringLength++;
		}

    //создаём массив переключателей для каждого символа в строке: если переключатель равен 0,
		//то символ ещё не участвовал в вычислениях, а после участия переключатель становится равен 1
		bool selector [stringLength];
		//заполняем массив нулями
		memset(selector, 0, stringLength * sizeof(bool));

		//создаём массив для левых скобок
		int bracketPosition[bracketCounter];
		
		//создаём массив для хранения значений в скобках
		int bracketValue[bracketCounter];
		
		//создаём массив для хранения кол-ва знаков в скобках, заполняем нулями
		int signsInBracket[bracketCounter];
		memset(signsInBracket, 0, sizeof(int));


		int j = 0; //счётчик для массива скобок

		//сканируем строку и заносим в массив скобок их позиции
		for (int i = 0; *(formula+i) != '\0'; i++)
		{
			if (*(formula+i) == '(')
			{
				bracketPosition[j] = i;

				j++;
			}
		}


		//рассматриваем содержимое скобок, начиная с самых последних
		for (int k = sizeof(bracketPosition) / sizeof(bracketPosition[0]) - 1; k >= 0; k--)
		{
			*pointer = bracketPosition[k] + 1; //устанавливаем курсор на скобку, прибавляем 1, чтобы перепрыгнуть скобку
		
			int counter;

			//считаем кол-во арифметических знаков внутри k-тых скобок для создания массива для чисел из k-тых скобок
			//цикл выполняется, пока не встретится правая скобка, которая ни разу не использовалась ранее
			for (counter = *pointer; !(*(formula + counter) == ')' && selector [counter] == 0); counter++)
			{
				//если знак появляется впервые, он учитывается
				if (selector [counter] == 0  &&  ( *(formula + counter) == '+' || *(formula + counter) == '-'
						|| *(formula + counter) == '*' || *(formula + counter) == '/') )
				{
					signsInBracket[k]++;
				}
			}

			for (int i = bracketPosition[k]; i <= counter; i++)
			{
				selector [i] = 1;
			}
		
		}

		//обратно обнуляем все переключатели для дальнейшей работы
		for (int i = 0; *(formula + i) != '\0'; i++)
		{
			selector [i] = 0;
		}



		//в этом цикле производится вычисление значений во всех скобках, начиная с последней
		for (int k = sizeof(bracketPosition) / sizeof(bracketPosition[0]) - 1; k >= 0; k--)
		{
			float num[signsInBracket[k] + 1]; //в этот массив будем заносить все значения чисел и скобок подряд
			int index = 0;
			int bracketIndex = k;
			bool isMinusTheFirst = 0; //проверяем, стоит ли минус перед первым значением в k-тых скобках
			int counter = bracketPosition[k] + 1; //устанавливаем курсор на скобку, прибавляем 1, чтобы перепрыгнуть скобку

			//цикл выполняется, пока не встретится правая скобка, которая ни разу не использовалась ранее
			//то есть рассматривается область внутри k-тых скобок
			while ( ! ( *(formula + counter) == ')' && selector [counter] == 0 ) )
			{
				//если символ - пробел
				if ( *(formula + counter) == ' ' )
				{
					counter++;
				}

				//если натыкаемся на левую скобку
				else if ( *(formula + counter) == '(' )
				{
					bracketIndex++;
					//необходимо учитывать только первый "слой" скобок, поскольку все остальные уже учтены внутри него
					if (selector [ counter - 1 ] == 0)
					{
						num[index] = bracketValue[bracketIndex];
						index++;
						counter++;
					}
					//если скобки уже учтены ранее, selector == 1, и мы их просто пропускаем
					else
					{
						counter++;
					}
				}

				//иначе если встречаем минус впервые и раньше всех значений в k-тых скобках
				else if (selector [counter] == 0  &&  index == 0  &&  ( *(formula + counter) == '-' ) )
				{
					isMinusTheFirst = 1;
					counter++;
				}

				//иначе если символ встречается впервые и не является арифметическим знаком, переводим все символы,
				//начиная с него, в число при помощи функции convert_float, выполнение которой прекращается при встрече
				//арифметического знака или правой скобки
				else if ( selector [ counter ] == 0  &&  ( *(formula + counter) != '+' )  &&  ( *(formula + counter) != '-' )
						&&  ( *(formula + counter) != '*' )  &&  ( *(formula + counter) != '/' ) )
				{
					*pointer = counter;
					num[index] = convert_float (formula, pointer); //в ходе выполнения convert_float произойдёт перенос курсора
					counter = *pointer;
					index++;
				}

				//иначе, если символы уже были использованы и учтены ранее, т.е. seletor [*pointer] == 1 или если встретится
				//арифметический знак или правая скобка, то переходим к рассмотрению следующего символа
				else
				{
					counter++;
				}
			}


			//получили массив чисел num, в котором по порядку записаны все числа, участвующие в вычислениях в k-тых скобках



			counter = bracketPosition[k] + 1; //устанавливаем курсор в первоначальное положение
			int sign; //считает знаки
			//если минус не стоит первым, то
			if (isMinusTheFirst == 0)
			{
				sign = 1;
				bracketValue[k] = num[0]; //предварительно присваиваем скобке значение первого участвующего в вычислениях числа
			}
			//иначе присваиваем скобке ноль, чтобы вычесть из него первое число
			else
			{
				sign = 0;
				bracketValue[k] = 0;
			}


			//теперь заново запускаем цикл while, идём слева направо и как только обнаруживаем знак, берём значения слева
			//и справа от него и производим вычисление

			//цикл выполняется, пока не встретится правая скобка, которая ни разу не использовалась ранее
			//то есть рассматривается область внутри k-тых скобок
			while ( ! ( *(formula + counter) == ')' && selector [counter] == 0 ) )
			{
				if (selector [counter] == 0)
				{
					switch ( *(formula + counter) )
					{
					case '+':
						bracketValue[k] = bracketValue[k] + num[sign];
						sign++;
						break;

					case '-':
						bracketValue[k] = bracketValue[k] - num[sign];
						sign++;
						break;

					case '*':
						bracketValue[k] = bracketValue[k] * num[sign];
						sign++;
						break;

					case '/':
						bracketValue[k] = bracketValue[k] / num[sign];
						sign++;
						break;

					default:
						break;
					}
				}

				counter++;
			}

			//таким образом, из цикла мы выйдем при указателе на правую скобку k-тых скобок


			//выставляем переключатель всех символов в k-тых скобках равным 1
			for (int i = bracketPosition[k]; i <= counter; i++)
			{
				selector [i] = 1;
			}
		}




		//теперь возвращаемся в самое начало строки и рассматриваем её всю целиком

		int signsInString = 0; //счётчик неучтенных знаков в строке целиком

		for (int i = 0; *(formula + i) != '\0'; i++)
		{
			//если знак появляется впервые, он учитывается
			if (selector [i] == 0  &&  ( *(formula + i) == '+' || *(formula + i) == '-' || *(formula + i) == '*'
					|| *(formula + i) == '/'))
			{
				signsInString++;
			}
		}


		float num[signsInString + 1]; //в этот массив будем заносить все значения чисел и скобок подряд
		int index = 0;
		int bracketIndex = -1; //т.к. самая первая скобка в строке имеет индекс 0
		bool isMinusTheFirst = 0; //проверяем, стоит ли минус перед первым значением в k-тых скобках
		int counter = 0;

		while (*(formula + counter) != '\0')
		{
			//если символ - пробел
			if ( *(formula + counter) == ' ' )
			{
				counter++;
			}

			//если натыкаемся на левую скобку
			else if ( *(formula + counter) == '(' )
			{
				bracketIndex++;
				//необходимо учитывать только первый "слой" скобок, поскольку все остальные уже учтены внутри него
				if (selector [ counter - 1 ] == 0 || counter == 0)
				{
					num[index] = bracketValue[bracketIndex];
					index++;
					counter++;
				}
				else
				{
					counter++;
				}
			}

			//иначе если встречаем минус впервые и раньше всех значений в k-тых скобках
			else if (selector [ counter ] == 0  &&  index == 0  &&  ( *(formula + counter) == '-' ) )
			{
				isMinusTheFirst = 1;
				counter++;
			}

			//иначе если символ встречается впервые и не является арифметическим знаком, переводим все символы,
			//начиная с него, в число при помощи функции convert_float, выполнение которой прекращается при встрече
			//арифметического знака или правой скобки
			else if ( selector [ counter ] == 0  &&  ( *(formula + counter) != '+' )  &&  ( *(formula + counter) != '-' )
					&&  ( *(formula + counter) != '*' )  &&  ( *(formula + counter) != '/' ) )
			{
				*pointer = counter;
				num[index] = convert_float (formula, pointer); //в ходе выполнения convert_float произойдёт перенос курсора
				index++;
				counter = *pointer;
			}
			else
			{
				counter++;
			}
		}

		//получили массив чисел num, в котором по порядку записаны все числа, участвующие в вычислениях в k-тых скобках

		counter = 0; //устанавливаем курсор в первоначальное положение
		int sign; //считает знаки
		//если минус не стоит первым, то
		if (isMinusTheFirst == 0)
		{
			sign = 1;
			total = num[0]; //предварительно присваиваем строке значение первого участвующего в вычислениях числа
		}
		//если минус первый, то присваиваем строке ноль, чтобы вычесть из него первое число
		else
		{
			sign = 0;
			total = 0;
		}

		//теперь запускаем цикл for, идём слева направо и как только обнаруживаем знак, берём значения слева
		//и справа от него и производим вычисление

		//цикл выполняется, пока не встретится правая скобка, которая ни разу не использовалась ранее
		//то есть рассматривается область внутри k-тых скобок
		for (counter = 0; *(formula + counter) != '\0'; counter++)
		{
			if (selector [counter] == 0)
			{
				switch ( *(formula + counter) )
				{
				case '+':
					total = total + num[sign];
					sign++;
					break;

				case '-':
					total = total - num[sign];
					sign++;
					break;

				case '*':
					total = total * num[sign];
					sign++;
					break;

				case '/':
					total = total / num[sign];
					sign++;
					break;

				default:
					break;
				}
			}
		}

	return total;
}
