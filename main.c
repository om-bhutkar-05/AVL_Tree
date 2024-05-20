#include"functions.c"
int main(){
avl root;
init(&root);
insert(&root,5);
insert(&root,7);
insert(&root,6);
insert(&root,3);
insert(&root,2);
insert(&root,1);
traversal(root);
printf("\n");
removenode(&root,5);
traversal(root);
}