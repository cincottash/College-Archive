

class Model{
    // object dimensions
    int canvasWidth;
    int canvasHeight;
    int imgWidth;
    int imgHeight;
    
    final double xIncr = 6;
    final double yIncr = 2;
    
    double xloc = 0;
    double yloc = 0;


    String dir = "SOUTHEAST";
    
    public Model(int canvasWidth, int canvasHeight, int imgWidth, int imgHeight) {
    	this.canvasWidth = canvasWidth;
    	this.canvasHeight = canvasHeight;
    	this.imgWidth = imgWidth;
    	this.imgHeight = imgHeight;
    	
    }
    
    //increment the x and y coordinates, alter direction if necessary
    public void updateLocationandDirection(int ButtonState) {
    	if(ButtonState == 0) {
    		xloc+=0;
    		yloc+=0;
    	}
    	
    	else {
    		switch(dir) {
    		case "NORTH":
    			if ((yloc-yIncr) <= 0) {
                    dir = "SOUTH";   
                }
                else {
                    yloc-=yIncr;
                }
                break;
    		case "NORTHEAST":
    			if ((xloc+xIncr+imgWidth) >= canvasWidth) {
                    
                    dir = "NORTHWEST";   
                }
                else if ((yloc-yIncr) <= 0) {
                    
                    dir = "SOUTHEAST"; 
                }
                else {
                    xloc+=xIncr;
                    yloc-=yIncr;
                }
                break;
    		case "EAST":
    			if ((xloc+xIncr+imgWidth) >= canvasWidth) {
                    
                    dir = "WEST";
                }
                else {
                    xloc+=xIncr;
                }
                break;
    		case "SOUTHEAST":
    			if ((xloc+xIncr+imgWidth) >= canvasWidth) {
                    
                    dir = "SOUTHWEST";
                }
                else if ((yloc+yIncr+imgHeight) >= canvasHeight) {
                    
                    dir = "NORTHEAST"; 
                }
                else {
                    xloc+=xIncr;
                    yloc+=yIncr;
                }
                break;
    		case "SOUTH":
    			if ((yloc+yIncr+imgHeight) >= canvasHeight) {
                    
                    dir = "NORTH"; 
                }
                else {
                    yloc+=yIncr;
                }
                break;
    		case "SOUTHWEST":
    			if ((xloc-xIncr) <= 0) {
                    
                    dir = "SOUTHEAST";
                }
                else if ((yloc+yIncr+imgHeight) >= canvasHeight) {
                    
                    dir = "NORTHWEST";
                }
                else {
                    xloc-=xIncr;
                    yloc+=yIncr;
                }
                break;
    		case "WEST":
    			if ((xloc-xIncr) <= 0) {
                    
                    dir = "EAST";
                }
                else {
                    xloc-=xIncr;
                }
                break;
    		case "NORTHWEST":
    			if ((xloc-xIncr) <= 0) {
                    
                    dir = "NORTHEAST";
                }
                else if ((yloc-yIncr) <= 0) {
                    
                    dir = "SOUTHWEST";
                }
                else {
                    xloc-=xIncr;
                    yloc-=yIncr;
                }
                break;
    	}
    	}
    	
    	
    	
    }//updateLocationandDirection
    
    public double getX() {
    	return xloc;
    }
 
    public double getY() {
    	return yloc;
    }
    
    //returns an int representing which image we're going to use
    public String getDirection() {
    	return dir;
    }
    
    
    
}
