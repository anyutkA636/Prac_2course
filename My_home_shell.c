#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/file.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

#include <function.h>

#define BB 5 



int pid_dad, fd_change_out = -2, fd_change_in = -2;

char *Read_Str() {  // считываем строку
    char  sym, *s = NULL; 
    int count = 0;  // кол-во символов
    s = (char *)realloc(s, BB);
    count = 0;
    s[0] = 0;  
    do {
        sym = getchar(); //fgets(input)
        count++;
        if ((sym == '\n') || (sym == EOF)) 
            break;
        else {
            if (count % BB == 0)  // если необходимо, увеличиваем строку
                s = (char *) realloc (s, strlen(s) + BB);
            s[count - 1] = sym; 
        }       
    } while (1);

    if ((count - 1) % BB == 0) {  // увеличиваем, чтобы дописать конец строки
        s = (char *) realloc (s, sizeof(char) * count);
    }
    //printf("count = %d\n", count);
    s[count - 1] = '\0';
    //printf("s1 = %s\n", s);
    return s;
}

char **Parsing(char *str, int *size) { //обработка строки
    char **ans = NULL;
    int num = 0, i = 0;  // num - кол-во лексем, i - индекс в начальной строке
    ans = (char **) realloc (ans, sizeof(char *) * BB); //выделили память под список лексем
    while (1) {
        char *s = NULL; //обычное слово
        char *spec = NULL; // специальное слово
        int count = 0;
        while ((i < strlen(str)) && ((str[i] != '|') && (str[i] != '\t') && (str[i] != '&') && (str[i] != ' ') && (str[i] != '"') && (str[i] != '<') && (str[i] != '>') && (str[i] != ';') && (str[i] != '(') && (str[i] != ')'))) {
            if (count % BB == 0) 
                s = (char *) realloc (s, count + BB);  //слово без спец символов
            s[count] = str[i];
            count++;
            i++;
        }
        if (count != 0) {
            if (count % BB == 0) 
                s = (char *) realloc (s, strlen(s) + 1);  
            s[count] = '\0'; //дописываем символ конца строки к слову
            ans[num] = s;  // добавляем слово в список
            num++;
            if (num % BB == 0) 
                ans = (char **) realloc (ans, sizeof(char *) * (num + BB));  // увеличиваем при необходимости список
        }
        if (i >= strlen(str)) 
            break;
        else if ((str[i] == ';') || (str[i] == '<') || (str[i] == '(') || (str[i] == ')')) { 
            spec = (char *) realloc (spec, 2);
            spec[0] = str[i];
            spec[1] = '\0';
            i++;
        }
        else if ((str[i] =='|') || (str[i] == '>') || (str[i] == '&')) {  // обрабатываем повторяющиеся спец символы
            if (str[i + 1] == str[i]) {
                spec = (char *) realloc (spec, 3);
                spec[0] = str[i];
                spec[1] = str[i + 1];
                spec[2] = '\0';
                i = i + 2;
            }
            else {
                spec = (char *) realloc (spec, 2);
                spec[0] = str[i];
                spec[1] = '\0';
                i++;
            }
        }
        else     //пропускаем пробельные символы
            i++;
        if (spec != NULL) {
            ans[num] = spec;
            num++;
            if (num % BB == 0) 
                ans = (char **) realloc (ans, sizeof(char *) * (num + BB));
        }
    }
    *size = num; // возвр кол-во лексем
    return ans; //возвращаем список лексем
}

int Conv(char **arg, int begin, int end) {
    //printf("\nКонвейер из команд: \n");
    char *s;
    int name_fl, status;
    int i = begin, fl = 0;
    int pid, fd[2], fd_in = 0, num = 0;   // fd[0] - для чтения, fd[1] - для записи
    char *vec[end - begin + 1];
    while (i < end) {
        char *name = NULL;
        name_fl = 0;
        while ((i < end) && (strcmp(arg[i], "|") != 0)) {  //сравниваем лексему с |; вернет 0, если равны
            s = arg[i];
            if (name_fl == 0) { // первое упоминание
                name = arg[i];
                num++;
                vec[num - 1] = arg[i];
                name_fl = 1;
            }
            else {
                num++;
                vec[num - 1] = arg[i];
            }
            i++;
        }
        vec[num] = NULL; // признак окончания вектора
        pipe(fd);  //создаем канал
        if ((pid = fork()) == 0) { //сын
            dup2(fd_in, 0);  // перенаправляем ввод (теперь из fd_in)
            if ((fl == 0) && (fd_change_in != -2)) {
                dup2(fd_change_in, 0); // перенаправляем ввод 
            }
            if (i != end) {
                dup2(fd[1], 1); // перенаправляем вывод (в канал)
            }
            else if ((i == end) && (fd_change_out != -2)) {
                //printf("HERE\n");
                dup2(fd_change_out, 1); // перенаправляем вывод 
            }
            close(fd[0]);   
            //добавить обработку 3х команд
            if (strcmp(name, "cp") == 0) {
                printf("my command:\n");
                fun_cp(vec);
            } 
            else if (strcmp(name, "sort") == 0) {
                printf("my command:\n");
                fun_sort(name);
            } 
            else if (strcmp(name, "cat") == 0) {
                printf("my command:\n");
                fun_cat(vec);
            } 
            else {
                execvp(name, vec);  //имя в текущей директории
                printf("The command does not exist.\n"); // не успешное выполнение
                exit(-1);
            }
        }
        else {  // отец
            wait(&status);
            close(fd[1]);
            fd_in = fd[0];  // читаем из канала
        }
        fl = 1;
        i++;
        //while (wait(NULL) != -1);
        num = 0;
    }
    close(fd[0]); 
    //printf("\n");
    return WEXITSTATUS(status);
}

void Redirection(char *how, char *to) { //анализ перенаправления
    //printf("\n");
    if (strcmp(how, "<") == 0) {
        //printf("Перенаправление ввода в файл %s\n", to);
        fd_change_in = open(to, O_RDONLY, 0666); 
    }
    else if (strcmp(how, ">") == 0) {
        //printf("Перенаправление вывода в файл %s, содержимое отбрасывается\n", to);
        fd_change_out = open(to, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    }
    else  if (strcmp(how, ">>") == 0) {
        //printf("Перенаправление вывода в файл %s, содержимое сохраняется\n", to);
        fd_change_out = open(to, O_WRONLY | O_CREAT | O_APPEND, 0666);
    }
}

int Shell_Com(char **arg, int begin, int end) { 
    int a = begin, b = end, status;
    for (int i = begin; i < end; ++i) {
        if ((strcmp(arg[i], "<") == 0) || (strcmp(arg[i], ">") == 0) || (strcmp(arg[i], ">>") == 0)) { // смотрим, есть ли перенаправления
            Redirection(arg[i], arg[i + 1]);
            if (i == a) 
                a += 2;
            else 
                b -= 2;           
        }
    } 
    status = Conv(arg, a, b);
    if (fd_change_out >= 0) 
        close(fd_change_out);

    if (fd_change_in >= 0) 
        close(fd_change_in);

    fd_change_out = -2; 
    fd_change_in = -2;

    return status;
}    


void Shell_If(char **arg, int begin, int end) {  // && and ||
    if (begin >= end) {
        return;
    }
    char *s;
    for (int i = begin; i < end; ++i) {
        if (strcmp(arg[i], "&&") == 0) { 
            //printf("Если команда : ");
            for (int j = begin; j < i; ++j) {
                s = arg[j];
                //printf("%s ", s);   
            }
            if (Shell_Com(arg, begin, i) == 0) {
                Shell_If(arg, i + 1, end);
            }
            //printf("завершилась успешно, то выполним ");
            //printf("\n");
            //Shell_If(arg, i + 1, end);
            return;
        }
        else if (strcmp(arg[i], "||") == 0) { 
            //printf("Если команда : ");
            for (int j = begin; j < i; ++j) {
                //char *s;
                s = arg[j];
                //printf("%s ", s);   
            }
            //Shell_Com(arg, begin, i);
            //printf("завершилась неуспешно, то выполним ");
            //printf("\n");
            //Shell_If(arg, i + 1, end);
             if (Shell_Com(arg, begin, i) != 0) {
                Shell_If(arg, i + 1, end);
            }
            return;
          }
    }
    //printf("Команда: ");
    //char *s;
    for (int j = begin; j < end; ++j) {
        s = arg[j];
        //printf("%s ", s);   
    }
    Shell_Com(arg, begin, end);
    //printf("\n\n");
}


void Shell_Command(char **arg, int begin, int end) { 
    if (begin >= end) {
        return;
    }
    char *s;
    for (int i = begin; i < end; ++i) {
        if (strcmp(arg[i], ";") == 0) {
            if (begin >= end) {
                printf("Incorrect data.\n");
                return;
            }
            if (begin == i) { 
                printf("Incorrect data.\n");
                //Shell_Command(arg, i + 1, end);
                return;
            }
            //printf("Команда с условным выполнением (;): ");
            for (int j = begin; j < i; j++) {
                s = arg[j];
                //printf("%s ", s); 
            }
            //printf("\n");
            Shell_If(arg, begin, i);
            Shell_Command(arg, i + 1, end);
            return;
        }
        else if (strcmp(arg[i], "&") == 0) { 
            if (begin >= end) {
                printf("Incorrect data.\n");
                return;
            }
            if (begin == i) { 
                printf("Incorrect data.\n");
                //Shell_Command(arg, i + 1, end);
                return;
            }
            for (int j = begin; j < i; ++j) {
                s = arg[j];
            }
            int pid;
            if ((pid = fork()) < 0) {
                printf("err\n");
            }
            else if (!pid) {  //сын
                int pid_son;
                if ((pid_son = fork()) < 0) {
                    printf("errr\n");
                }
                else if (!pid_son) {
                    signal(SIGINT, SIG_IGN);
                    int in_ign = open("/dev/null", O_RDONLY, 0666);
                    dup2(in_ign, 0);
                    sleep(1);
                    Shell_If(arg, begin, i);
                    exit(0);
                }
                else 
                    exit(0);
            }
            else 
                wait(NULL);
            
            Shell_Command(arg, i + 1, end);
            return;
        }    
    
    }
    if (begin >= end) {
        return;
    }
    //printf("Команда с условным выполнением: ");
    for (int j = begin; j < end; ++j) {
        fflush(stdout);
        s = arg[j];
        //printf("%s ", s);      
    }
    //printf("\n");
    Shell_If(arg, begin, end);
    return;
}


int Bracket(char **arg, int begin, int end) { 
    int st = 0, en = 0, i, flag = 0;
    int balance = 0;
    if (begin >= end) 
        return -1;
    while (1) {
        st = 0;
        en = 0;
        for (i = begin; i < end; i++) {
            if (strcmp(arg[i], "(") == 0) {
                st = i + 1;
                balance = 1;
                flag = 1;
                break;
            }
        }
        for (int i = st; i < end; i++) {
            if (strcmp(arg[i], "(") == 0) 
                balance++;
            if (strcmp(arg[i], ")") == 0) {
                if (balance == 1) {
                    en = i;
                    break;
                }
                else 
                    balance--;
            }
        }
        if (st == en && flag == 0)  //скобок не было
            return 0; 
        else if (flag == 1) {
            //printf("Sorry, My_shell can not handle brackets.\n");
            return -2;
        }
    }
    return 0;

}


int main(void) {
    while (1) {
        char **arg = NULL; // список лексем
        char *str = NULL;  //буферная строка
        int num; // кол-во лексем
        fflush(stdin); // сбрасывает буфер
        printf("$ ");  // приглашение
        str = Read_Str();
        while ((str[0] == '\n') || (str[0] == '\t') || (strlen(str) == 0)) { //пропускаем пустые строки
            printf("$ "); 
            str = Read_Str();
        }
        //str[strlen(str)] = '\0';
        //printf("s = %s\n", str);
        arg = Parsing(str, &num); // обрабатываем строку
        if (arg == NULL) {
            printf("Incorrect data.\n");
            return 0;
        }
        int incor = 0;
        for (int i = 0; i < num; i++) {
        //printf("arg[i]: %s\n", arg[i]);
            if ((strcmp(arg[i], "<") == 0) || (strcmp(arg[i], ">") == 0) || (strcmp(arg[i], ">>") == 0) || (strcmp(arg[i], ";") == 0) ||
                (strcmp(arg[i], "|") == 0) || (strcmp(arg[i], "||") == 0) || (strcmp(arg[i], "&&") == 0) || (strcmp(arg[i], "&") == 0)) {
            if (!((strcmp(arg[i], "&") == 0) && i == num-1)) {
                    if (i == 0 || i == num-1) {
                            incor = 1;
                            break;
                    }
        }
                int j = i + 1;
        //printf("arg[i+1]: %s\n", arg[j]);

                if ((strcmp(arg[j], "<") == 0) || (strcmp(arg[j], ">") == 0) || (strcmp(arg[j], ">>") == 0) || (strcmp(arg[j], ";") == 0) ||
                    (strcmp(arg[j], "|") == 0) || (strcmp(arg[j], "||") == 0) || (strcmp(arg[j], "&") == 0) || (strcmp(arg[j], "&&") == 0)) {
                //printf("ok+1\n");
                        incor = 1;
                        break;
                }
                j -= 2;
        //printf("arg[j-1]: %s\n", arg[j]);

                if ((strcmp(arg[j], "<") == 0) || (strcmp(arg[j], ">") == 0) || (strcmp(arg[j], ">>") == 0) || (strcmp(arg[j], ";") == 0) ||
                    (strcmp(arg[j], "|") == 0) || (strcmp(arg[j], "||") == 0) || (strcmp(arg[j], "&") == 0) || (strcmp(arg[j], "&&") == 0)) {
                        //printf("ok+1\n");
                        incor = 1;
                        break;
                }
            }
        }

        if (incor) {
            printf("Incorrect data.\n");
            continue;
        }

        int open = 0;
        for (int i = 0; i < num; ++i) {
            if (strcmp(arg[i], ")") == 0) 
                open--;
            else if (strcmp(arg[i], "(") == 0) 
                open++;
            if (open < 0) {
                printf("Brackets are placed incorrectly. There is not balance.\n");
                break;
            }
        }
        if (open > 0) {
            printf("Brackets are placed incorrectly. There is not balance.\n");
            continue;
        }
        int er = Bracket(arg, 0, num);
        if (er == -1) {
            printf("Brackets are placed incorrectly. Expected word before ).\n");
            continue;
        }
        else if (er == -2) {
            printf("Sorry, My_shell can not handle brackets.\n");
            continue;
        }
        Shell_Command(arg, 0, num);
        //printf("%d, %d\n", getpid(), pid_dad);
        for (int i = 0; i < num; ++i) 
            free(arg[i]);
        free(arg);
        free(str);
    }
   return 0;
}
