#include <string.h>  /* for memmove */

#define TRUE 1
#define FALSE 0

char[] b;
int i,     /* offset into b */
i_end, /* offset to end of stemmed word */
j, k;
int INC = 50;
                     /* unit of size whereby b is increased */

int main(){
	b = new char[INC];
    i = 0;
    i_end = 0;
    char[] w = new char[501];
    for (int i = 0; i < args.length; i++){
        FileInputStream in = new FileInputStream(args[i]);
		while(true)
           {  int ch = in.read();
              if (Character.isLetter((char) ch))
              {
                 int j = 0;
                 while(true)
                 {  ch = Character.toLowerCase((char) ch);
                    w[j] = (char) ch;
                    if (j < 500) j++;
                    ch = in.read();
                    if (!Character.isLetter((char) ch))
                    {
                       /* to test add(char ch) */
                       for (int c = 0; c < j; c++) s.add(w[c]);

                       /* or, to test add(char[] w, int j) */
                       /* s.add(w, j); */

                       s.stem();
                       {  String u;

                          /* and now, to test toString() : */
                          u = s.toString();

                          /* to test getResultBuffer(), getResultLength() : */
                          /* u = new String(s.getResultBuffer(), 0, s.getResultLength()); */

                          System.out.print(u);
                       }
                       break;
                    }
                 }
              }
              if (ch < 0) break;
              System.out.print((char)ch);
           }
       }
   }
}