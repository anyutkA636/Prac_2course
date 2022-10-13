/* 6.40. Описать функцию, которая формирует список L3, включая в него
элементы, которые входят в один из списков (L1 или L2), но при этом не входят
в другой. Список L3 формируется из копий звеньев списков L1 и L2; списки L1
и L2 не изменяются.
Тип данных - char∗. */ 



typedef struct s_list {
	char *c;
	struct s_list *next;
} t_list;

	

// элементы входят в l1, но не входят в l2
t_list *new_list(t_list **l1, t_list **l2) { 
    t_list *l3 = NULL;
    if (l1 == NULL && l2 == NULL)
        return l3;
    else if (l1 == NULL)
        return *l2;
    else if (l2 == NULL)
        return *l1;
    else {
        t_list *tmp_l1 = *l1, *tmp_l2 = *l2;
        int flag = 0;
        while (tmp_l1 != NULL) {
            flag = 0;
            temp_l2 = *l2;
            while (tmp_l2 != NULL && flag == 0) {
                if (tmp_l1 -> c == tmp_l2 -> c) {
                    flag = 1;
                    break;
                }
                tmp_l2 = tmp_l2 -> next;
            }
            if (flag == 0) {
                t_list *new = (t_list *) malloc(sizeof(t_list));
	            new -> c = tmp_l2 -> c;
	            new -> next = l3;
	            l3 = new;
            }
        }
        return l3;
    }
}
