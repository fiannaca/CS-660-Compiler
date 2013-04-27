int x ,y ;
int z ; 
int main()
{
  
  z = x + y ; 
  z = x * y ; 

 /* 
  BUG IN AST CODE 
  z = ( x + y ) * ( x - y ) ; 
 */ 
 if (z ) 
 {
     z = x - y;

 }
 while (x )
 {

   x++;
   z--; 

 }

   return  0 ; 

}
