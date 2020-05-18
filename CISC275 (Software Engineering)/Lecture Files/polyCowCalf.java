
class Cow {
    String noise = "moo";
    
    String speak(){
	return noise;
    }
    void converse(Cow c1){
	System.out.println( this.speak() + " to you; " + c1.speak() );
    }
}
class Calf extends Cow {
    String sound = "meh";
    String speak(){
	return sound;
    }
    void converse(Calf c1){
	System.out.println( this.speak() + "(Calf) to you; " + c1.speak() );
    }
}

class Main {
    public static void main(String[] a){
	Cow c1 = new Cow();
	Calf c3 = new Calf();
	Cow c2 = c3;
	
	System.out.println( c1.speak() );  //__________________________1
	System.out.println( c2.speak() );  //__________________________2
	c1.converse(c3);                   //__________________________3
	c3.converse(c1);                   //__________________________4
	c1.converse(c2);                   //__________________________5
	c2.converse(c3);                   //__________________________6
	c3.converse(c3);                   //__________________________7
    }
}





//overloading vs. overriding
