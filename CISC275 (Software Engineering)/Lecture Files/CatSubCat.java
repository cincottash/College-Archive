class Cat {

        public String name = "Cat";
        public String toString(){return "Cat";}

        public static void printNames(Cat c1, Cat c2){
                System.out.println(c1.name + " " + c2.name);
        }
        
        public static void main(String[] args) {
                Cat c1 = new Cat();
                SubCat s1 = new SubCat();

                Cat.printNames(c1, s1);

                System.out.println(c1);

                Cat c2 = s1;

                System.out.println(c2.name);

                System.out.println(s1);
        }
}

class SubCat extends Cat{
        public String name = "SubCat";
        public String toString(){return "SubCat";}
    public int seven(return 7;)
}

// This code is bad style. That is the point.
//
// 1) Will this compile? If not, mark any errors and write corrections.
//
// 2) Assume the code will run as written. What will the main() in Cat print?

