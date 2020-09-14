package com.company.vishli;

import java.util.*;
/*java.util.* - импортируешь все, что есть в библиотеке import java.util.Scanner - импортируешь конкретно Scanner
* Для решения таких задач в Java используется сканер (от англ. Scanner).
* Запомните: если что-то ввели в консоли, а нам надо считать что же именно ввели  - используем сканер.
* Класс сканера в Java находится в пакете java.util. Java предоставляет различные способы чтения ввода с клавиатуры, одним из них является класс java.util.Scanner.

Класс Java Scanner разбивает входные данные на токены с помощью разделителя, который по умолчанию является пробелом.
 Он предоставляет множество методов для чтения и анализа различных примитивных значений.*/

public class POL {
    private static Stack<String> stack = new Stack<>();//полиз
    private static Stack<Double> resultStack = new Stack<Double>();//подсчёт результатов
    private static List<String>outString = new ArrayList<>();//главн строка действий
    private static Scanner scan = new Scanner(System.in);//считывание с клавиатуры
    public static void main(String[] args) {

/*Если при пустом стеке вызвать методы pop() или peek(), то программа закроется с ошибкой.
Чтобы избежать подобной ситуации, нужно обработать исключение EmptyStackException.
Тогда программа будет работать без сбоев.
Чтобы узнать, кто теперь последний в стеке, не удаляя его оттуда, нужно вызвать метод peek().

 */

        System.out.println((char) 27 + "[34mВВЕДИТЕ ЖЕЛАЕМЫЕ ОПЕРАЦИИ: " + (char)27 + "[0m");
        String exp; //ввод с клавиатуры
        exp = scan.nextLine();
        String b = exp.replaceAll(" ", "");
        String forDigits = "";
        char[]strToArray = b.toCharArray();
        int r = 0;
        int chk = 0;
        while(r<strToArray.length){

            while(isNumber(Character.toString(strToArray[r]))){
                if(r == strToArray.length-1){
                    chk++;
                    forDigits+=Character.toString(strToArray[r]);
                    break;
                }else{
                    chk++;
                    forDigits+=Character.toString(strToArray[r]);
                    if(!isNumber(Character.toString(strToArray[r+1]))){
                        break;
                    }else{
                        r++;
                    }

                }

            }

            if(chk==0){

                inOpn(Character.toString(strToArray[r]));

            }else{


                inOpn(forDigits);
                chk=0;
                forDigits = "";
            }

            r++;

        }
       /* StringTokenizer st1 = new StringTokenizer(exp.replaceAll("", " ")," ");//на отдельные символы без пробелы
        for (int i = 0; st1.hasMoreTokens(); i++) {
            inOpn(st1.nextToken());//метод построения полиза, на вход по символу
        }*/
/*Stack – это подкласс Vector, который реализует стандартный стек last-in, first-out.

В Java Stack только определяет стандартный конструктор, который создает пустой стек.
Stack включает все методы, определённые Vector, и самостоятельно добавляет несколько своих собственных.*/
        while(!stack.empty()){
/*Чтобы убедиться, что никого не осталось, вызываем метод empty(), который возвращает булево значение.
метод pop(). Как видите, мы не указываем позицию элемента, так стек работает только с последним элементом.
Возвращает элемент, находящийся в верхней части стэка, удаляя его в процессе.*/
            outString.add(stack.pop());

        }
        System.out.println((char) 27 + "[36mОБРАТНАЯ ПОЛЬСКАЯ ЗАПИСЬ(ПОЛИЗ): " + (char)27 + "[0m");

        for(String n:outString){
            System.out.print(n+" ");
        }
        System.out.println();
        for(int i = 0; i<outString.size();i++){
            if(isNumber(outString.get(i))){
                resultStack.push(Double.parseDouble(outString.get(i)));
            }else{
                double temp1 = resultStack.pop();
                double temp2 = resultStack.pop();

                switch(outString.get(i)){
                    case "+":
                        resultStack.push(temp1+temp2);
                        break;
                    case "-":
                        resultStack.push(temp2-temp1);
                        break;
                    case "*":
                        resultStack.push(temp1*temp2);
                        break;
                    case "/":
                        resultStack.push(temp2/temp1);
                        break;
                    case "^":
                        resultStack.push(Math.pow(temp2,temp1));
                }
            }

        }
        System.out.println((char) 27 + "[35mРЕЗУЛЬТАТ:\n " + (char)27 + "[0m"+ resultStack.pop());

    }
   /* Object push(Object element)
    Вталкивает элемент в стек. Элемент также возвращается.
    */
    static void inOpn(String token){//обратная запись


        if(isNumber(token)){
            outString.add(token);//пункт 1. если число-помещаем в стек
            //System.out.println(" ПЕРЕМ "+token+" ");
        }else if(stack.empty()){//пункт а
            stack.push(token);

        }else if (token.equals("(")){ //приоритет открывающая скобка
            stack.push(token);
        }

        else if(token.equals(")")){
            while(getPriority(stack.peek())!=1){//добавляем в стек пока не встретим открывающую
                outString.add(stack.pop());
            }
            stack.pop();
        }else if(getPriority(stack.peek())<getPriority(token)){//пункт а
            stack.push(token);
        }else if(getPriority(stack.peek())>=getPriority(token)){//пункт б
                while(!stack.empty()){//пока строка не станет пустой
                    if(getPriority(stack.peek())>=getPriority(token)){

                        outString.add(stack.pop());
                    }else{
                        break;
                    }
                }
            stack.push(token);
        }

    }




    static boolean isNumber(String token){//число или нет
        try{
            Integer.parseInt(token);
            return true;
        }catch(NumberFormatException ex){
            return false;
        }
    }
    private static int getPriority(String token) //на вход токен * \ старший приорит +- 2 (1
    {
        switch (token)
        {
            case "(":
                return 1;
            case "*": case "/":
            return 3;
            case "+": case "-":
            return 2;
            case "^":// возведение в степень
                return 4;
            default:
                return -10; //рандомное значение чтоб не ругался
        }
    }
}
