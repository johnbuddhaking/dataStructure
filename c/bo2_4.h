/*************************************************************************
	> File Name: bo2_4.h
	> Author: 
	> Mail: 
	> Created Time: 2019年03月17日 星期日 19时42分07秒
 ************************************************************************/

#ifndef _BO2_4_H
#define _BO2_4_H
Status PriorElem(LinkList L, ElemType cur_e, ElemType &pre_e){

    LNode* p = L;

    while(p->next){
        if(p->next->data == cur_e){
            pre_e = p->data;
            return OK;
        }

        p = p->next;
    }
    
    return ERROR;
}


Status NextElem(LinkList L, ElemType cur_e, ElemType &next_e){

    LNode* p = L;

    while(p){
        
        if(p->data == cur_e && p->next){
            next_e = p->next->data;
            return OK;
        }

        p = p->next;
    }

    return ERROR;
}

#endif
