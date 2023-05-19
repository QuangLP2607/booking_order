#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
typedef struct Node
{
    char ma_yeu_cau[8];
    int so_nguoi;
    char ma_ks[3];
    int so_phong;
    char day[11];
    int kids;
    struct Node* next;
}Node;
//ham tao node
Node *thisinh(char *ma_yeu_cau,int so_nguoi,char *ma_ks,int so_phong,char *day,int kids)
{
    Node *p = (Node *)malloc(sizeof(Node));
    strcpy(p->ma_yeu_cau, ma_yeu_cau);
    strcpy(p->ma_ks, ma_ks);
    strcpy(p->day, day);
    p->so_nguoi=so_nguoi;
    p->so_phong=so_phong;
    p->kids=kids;
    p->next = NULL;
    return p;
}
//them node vao cuoi danh sach
Node *insertLast(char *ma_yeu_cau,int so_nguoi,char *ma_ks,int so_phong,char *day,int kids, Node *root)
{
    Node *newNode = thisinh(ma_yeu_cau,so_nguoi,ma_ks,so_phong,day,kids);
    Node *p = root;
    if(root == NULL)
    {
        root = newNode;
    }
    else
    {
        while(p->next!=NULL) //tra ve nut o cuoi danh sach
            p=p->next;
        p->next = newNode;
    }
    return root;
}
//in danh sach
void prinlist(Node *root,int n)
{
    printf("so luong yeu cau duoc doc: %d\n",n);
    for (Node *p = root; p!= NULL; p = p->next)
    {
        printf("%s %d %d %s %s %d\n",p->ma_yeu_cau,p->so_nguoi,p->so_phong,p->ma_ks,p->day,p->kids);
    }
}
//so yeu cau khong hop le: co tre em phai co it nhat 1 nguoi lon
void khong_hop_le(Node *root)
{
    int n=0;
    printf("Yeu cau khong hop le:\n");
    for (Node *p = root; p!= NULL; p = p->next)
    {
        if(p->kids>0)
        {
            if(p->so_nguoi-p->kids==0)
            {
                n++;
                printf("%s %d %d %s %s %d\n",p->ma_yeu_cau,p->so_nguoi,p->so_phong,p->ma_ks,p->day,p->kids);
            }
        }
    }
    printf("Vay so yeu cau khong hop le la: %d\n",n);
}

//lay ngay he thong
void printCurrDate()
{
    time_t t=time(NULL);
    struct tm tm=*localtime(&t);
}
// cai dat cay tim kiem nhi phan
typedef struct BST
{
    char ma_yeu_cau[8];
    int so_nguoi;
    char ma_ks[3];
    int so_phong;
    char day[11];
    int kids;
    struct BST* leftChild;
    struct BST* rightChild;
}BST;

BST* makeTreeNode(char *ma_yeu_cau,int so_nguoi,char *ma_ks,int so_phong,char *day,int kids)
{
    BST* p = (BST*)malloc(sizeof(BST));
    strcpy(p->ma_yeu_cau, ma_yeu_cau);
    strcpy(p->ma_ks, ma_ks);
    strcpy(p->day, day);
    p->so_nguoi=so_nguoi;
    p->so_phong=so_phong;
    p->kids=kids;
    p->leftChild = NULL;
    p->rightChild = NULL;
    return p;
}

// Tra ve qua ten ham
BST* insert_tree(BST* r, char *ma_yeu_cau,int so_nguoi,char *ma_ks,int so_phong,char *day,int kids)
{
    if(r == NULL) return makeTreeNode(ma_yeu_cau,so_nguoi,ma_ks,so_phong,day,kids); // cay ban dau rong
    int c = strcmp(r->ma_yeu_cau,ma_yeu_cau);
    if(c == 0){
        printf("Ma yeu cau bi trung!\n");
        return r;
    }else if(c < 0){
        r->rightChild = insert_tree(r->rightChild,ma_yeu_cau,so_nguoi,ma_ks,so_phong,day,kids);
        return r;
    }else{
        r->leftChild = insert_tree(r->leftChild,ma_yeu_cau,so_nguoi,ma_ks,so_phong,day,kids);
        return r;
    }
}
//luu du lieu vao cay nhi phan
void load_tree(Node *root, BST **tree_root)
{

    do{
        *tree_root=insert_tree(*tree_root,root->ma_yeu_cau,root->so_nguoi,root->ma_ks,root->so_phong,root->day,root->kids);
        root=root->next;
    }while(root->next!=NULL);
}
// Tim kiem va tra ve nut tren cay
BST* find(BST* r, char* ma_yeu_cau)
{
    if(r == NULL) return NULL;
    int c = strcmp(r->ma_yeu_cau,ma_yeu_cau);
    if(c == 0) return r;
    if(c < 0) return find(r->rightChild,ma_yeu_cau);
    return find(r->leftChild,ma_yeu_cau);
}
void tim_kiem(BST* tree_root)
{
    char ma_yeu_cau[9];
    printf("\tNhap ma yeu cau: ");
    fflush(stdin);
    fgets(ma_yeu_cau, 10, stdin);
        ma_yeu_cau[strlen(ma_yeu_cau)-1]='\0';
    BST *yeu_cau=find(tree_root,ma_yeu_cau);
    if(yeu_cau==NULL)
        printf("Not found\n");
    else
        printf("Thong tin yeu cau:\n%s %d %d %s %s %d\n",yeu_cau->ma_yeu_cau,yeu_cau->so_nguoi,yeu_cau->so_phong,yeu_cau->ma_ks,yeu_cau->day,yeu_cau->kids);
}
//cap nhat yeu cau
void cap_nhat(BST *tree_root)
{
    char ma_yeu_cau[9];
    printf("nhap ma yeu cau muon cap nhat:");
    fflush(stdin);
    fgets(ma_yeu_cau, 10, stdin);
        ma_yeu_cau[strlen(ma_yeu_cau)-1]='\0';
    BST *yeu_cau=find(tree_root,ma_yeu_cau);
    if(yeu_cau==NULL)
        printf("Not found\n");
    else
    {
        int so_nguoi;
        char day[11];
        int kids;
        printf("nhap thong tin cap nhat:\n");
        printf("ngay-thang-nam: ");
        fflush(stdin);
        fgets(day, 10, stdin);
        day[strlen(day)-1]='\0';
        printf("so luong nguoi:");
        scanf("%d",&so_nguoi);
        printf("so luong tre em:");
        scanf("%d",&kids);
        if(yeu_cau->kids>0)
        {
            if(yeu_cau->so_nguoi-yeu_cau->kids==0)
            {
                printf("invalid\n");
            }
            else
            {
                printf("Update!");
                yeu_cau->so_nguoi=so_nguoi;
                yeu_cau->kids=kids;
                strcpy(yeu_cau->day,day);
            }
        }
    }
}
// tim nut trai nhat
BST* findMin(BST* r){
    if(r == NULL) return NULL;
    BST* lmin = findMin(r->leftChild);
    if(lmin != NULL) return lmin;
    return r;
}
// ham xoa nut
// Co the viet lai bang cach tra ve qua tham so
BST* huy_yeu_cau(BST* r, char* ma_yeu_cau){
    if(r == NULL) return NULL;
    int c = strcmp(r->ma_yeu_cau,ma_yeu_cau);
    if(c > 0) r->leftChild = huy_yeu_cau(r->leftChild,ma_yeu_cau);
    else if(c < 0) r->rightChild = huy_yeu_cau(r->rightChild,ma_yeu_cau);
    else{
        if(r->leftChild != NULL && r->rightChild != NULL){
            BST* tmp = findMin(r->rightChild);
            strcpy(r->ma_yeu_cau, tmp->ma_yeu_cau);
            strcpy(r->ma_ks, tmp->ma_ks);
            strcpy(r->day, tmp->day);
            r->so_nguoi=tmp->so_nguoi;
            r->so_phong=tmp->so_phong;
            r->kids=tmp->kids;
            r->rightChild = huy_yeu_cau(r->rightChild,tmp->ma_yeu_cau);
        }else{
            BST* tmp = r;
            if(r->leftChild == NULL) r = r->rightChild; else r = r->leftChild;
            free(tmp);   //giai phong bo nho
        }
    }
    return r;
}

void Huy(BST* tree_root)
{
    char ma_yeu_cau[9];
    printf("\tNhap ma yeu cau muon huy: ");
    fflush(stdin);
    fgets(ma_yeu_cau, 10, stdin);
        ma_yeu_cau[strlen(ma_yeu_cau)-1]='\0';
    BST *yeu_cau=find(tree_root,ma_yeu_cau);
    if(yeu_cau==NULL)
        printf("Not found\n");
    else
        printf("Delete\n");
        huy_yeu_cau(tree_root, ma_yeu_cau);
}
//khoi tao chuong trinh
Node *processLoad()
{
    Node *root=NULL;
    char filebien_so[]="booking_orders.txt";
    char line[256];
    FILE *f;
    char ma_yeu_cau[8];
    int so_nguoi;
    char ma_ks[4];
    int so_phong;
    char day[13];
    int kids;
    f = fopen(filebien_so, "r");
    if(f == NULL)
        printf("Load data -> file not found\n");
    int so_yc;
    fscanf(f,"%d",&so_yc);
    //printf("%d\n",so_yc);
    fgets(line, 256, f);
    while(fgets(line, 256, f) != NULL)
    {
        sscanf(line,"%s %d %d %s %s %d",ma_yeu_cau,&so_nguoi,&so_phong,ma_ks,day,&kids);
        //printf("%s %d %d %s %s %d　\n",ma_yeu_cau,so_nguoi,so_phong,ma_ks,day,kids);
        root=insertLast(ma_yeu_cau,so_nguoi,ma_ks,so_phong,day,kids,root);
    }
    prinlist(root,so_yc);
    fclose(f);
    return root;
}

void menu()
{
    printf("\n________________________________\n");
    printf("Chuong trinh quan ly dat phong \n");
    printf("Vui long chon mot trong cac chuc nang sau \n");
    printf("1) Doc du lieu tu file log\n");
    printf("2) Kiem tra so luong yeu cau khong hop le\n");
    printf("3) Tra cuu theo ma yeu cau\n");
    printf("4) Thay doi yeu cau\n");
    printf("5) huy yeu cau\n");
    printf("6) Ket thuc chuong trinh\n");
}
int main()
{
    BST *tree_root =NULL;
    Node *root =NULL;
    int choose;
    do{
        menu();
        printf("   Choose your option: ");
        scanf("%d",&choose);
        switch (choose)
        {
            case 1: root = processLoad();
                    load_tree(root,&tree_root);
                break;
            case 2:khong_hop_le(root);
                break;
            case 3:tim_kiem(tree_root);
                break;
            case 4: cap_nhat(tree_root);
                break;
            case 5:Huy(tree_root);
                break;
        }
    }while(choose != 9);
    return 0;
}
