class Cow {
    String noise = "moo";

    String speak(){
		return noise;
    }

    void converse(Cow c1){
		System.out.println( this.speak() + " to you; " + c1.speak() );
    }

    public static void main(String[] args){
		Cow c1 = new Cow();
		Calf c3 = new Calf();
		Cow c2 = c3;

		System.out.println( c1.speak() ); 
		
		System.out.println( c2.speak() );  
		
		c1.converse(c3);                 
		
		c3.converse(c1);                  
		
		c1.converse(c2);               
		
		c2.converse(c3);
		
		c3.converse(c3);                   
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

@Override
public boolean equals(Object o){
	equals  = false;
	if(o instanceof Dog){
		Dog other = Dog(o);
		equals = other.name.equals(o.name);
	}
	return(equals);
}

@Override
public int hashCode(){
	return(this.name);
}