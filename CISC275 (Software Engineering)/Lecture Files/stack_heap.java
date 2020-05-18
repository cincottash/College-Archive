class MyStrings{

    /*
     * Write what is printed, or "error" if a line causes an error
     * that prevents printing.
     */
    
    public static void main(String[] argyle){

        String s1 = "dog";
        String s2 = "cat";
        String s3 = "dogcat";

        String temp  = s1 + s2;
                
        System.out.println("1. " + (temp == s3));              //1
        System.out.println("2. " + temp.equals(s3));           //2

        Cow c1 = new Cow();
        Cow c2 = new Cow();
        
        System.out.println("3. " + (c1.name == c2.name));      //3
        System.out.println("4. " + c1.name.equals(c2.name));   //4

        c1.name = new String("Bossie");
        System.out.println("5. " + (c1.name == c2.name));      //5
        System.out.println("6. " + c1.name.equals(c2.name));   //6

        c1.name = c2.name;
        c2.name.replace('o','e'); 
        System.out.println("7. " + (c1.name == c2.name));      //7
        System.out.println("8. " + c1.name.equals(c2.name));   //8
        System.out.println("9. " + c1.name);                   //9
        System.out.println("10. " + c2.name);                  //10
    }
}

class Cow {
    public String name = "Bossie";
    public String toString(){return name;}
}
