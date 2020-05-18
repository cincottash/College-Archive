
/** 
* This is the model component of the MVS software design pattern.
* Stores the data for the domain you are modeling, along with the logic related to that raw data
    * @author Shane Cincotta 
*/



public class Model{
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

         /** 
*Model constructor
    * @param canvasWidth Pixel width of canvas
    * @param canvasHeight Pixel height of canvas
    * @param imgWidth Pixel width of the image
    * @param imgHeight Pixel height of the image
    * @return Returns a new instance of the class
*/
    
    public Model(int canvasWidth, int canvasHeight, int imgWidth, int imgHeight) {
    	this.canvasWidth = canvasWidth;
    	this.canvasHeight = canvasHeight;
    	this.imgWidth = imgWidth;
    	this.imgHeight = imgHeight;
    	
    }
    
             /** 
*Increment the x and y coordinates, alter direction if necessary
*/

    public void updateLocationandDirection() {
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
    	
    }//updateLocationandDirection
    
             /** 
*Gets the current x location
    * @return Returns a double representing the x coordinate
*/

    public double getX() {
    	return xloc;
    }
 
                 /** 
*Gets the current y location
    * @return Returns a double representing the y coordinate
*/

    public double getY() {
    	return yloc;
    }

                     /** 
*Gets the current direction
    * @return returns an int representing which direction the image should move
*/
    
    public String getDirection() {
    	return dir;
    }
    
    
    
}
