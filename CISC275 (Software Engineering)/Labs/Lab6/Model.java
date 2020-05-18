import java.awt.event.*;

public class Model implements KeyListener {
    public int width;
    public int height;
    public int imgWidth;
    public int imgHeight;
    public int xloc;
    public int yloc;
    public Direction dir = Direction.EAST;
    final double xIncr = 8;
    final double yIncr = 2;
    //static int picInd = 0;
    //final int canvasCount = 10;
    //int x;
    //Random rand = new Random();
    
    
    public Model(int width, int height, int imgWidth, int imgHeight){
        this.width = width;
        this.height = height;
        this.imgWidth = imgWidth;
        this.imgHeight = imgHeight;
    }
    
    public void keyPressed(KeyEvent event) {
        if (event.getKeyCode() == KeyEvent.VK_LEFT) {
            dir = Direction.WEST;
        }
        if (event.getKeyCode() == KeyEvent.VK_DOWN) {
            dir = Direction.SOUTH;
            //cTDirection = DOWN;
        }
        if (event.getKeyCode() == KeyEvent.VK_RIGHT) {
            dir = Direction.EAST;
            //cTDirection = RIGHT;
        }
        if (event.getKeyCode() == KeyEvent.VK_UP) {
            dir = Direction.NORTH;
            //cTDirection = UP;
        }
    }
    public void keyReleased(KeyEvent e) {
       // displayInfo(e, "KEY RELEASED: ");
    }
    public void keyTyped(KeyEvent e) {
        //displayInfo(e, "KEY TYPED: ");
    }
    
    public void updateLocationandDirection(){
        switch (dir){
                case EAST:
                 	if ((xloc + xIncr + imgWidth) >= width) {  
                         //dir = Direction.WEST;
                         xloc = xloc;
                     }
                     else {
                         xloc += xIncr;
                     }
                     break; 
                 //Forward North
                 case NORTH: 
                 	if ((yloc - yIncr) <= 0) {
                         //dir = Direction.SOUTH;
                         yloc = yloc;   
                     }
                     else {
                         yloc -= yIncr;
                     }
                     break; 
                case SOUTH: 
                 	if ((yloc + yIncr + imgHeight) >= height) {
                         //dir = Direction.NORTH; 
                         yloc = yloc;
                     }
                     else {
                         yloc += yIncr;
                     }
                     break; 
                case WEST: 
                 	if ((xloc - xIncr) <= 0) {
                         //dir = Direction.EAST;
                         xloc = xloc;
                     }
                     else {
                         xloc -= xIncr;
                     }
                     break;
        }
            
         // switch (dir) { 
//          //E0, N1, NE2, NW3, S4, SE5, SW6 , W7
//                 //Forward East
//                 case EAST:
//                 	if ((xloc + xIncr + imgWidth) >= width) {  
//                         dir = Direction.WEST;
//                     }
//                     else {
//                         xloc += xIncr;
//                     }
//                     break; 
//                 //Forward North
//                 case NORTH: 
//                 	if ((yloc - yIncr) <= 0) {
//                         dir = Direction.SOUTH;   
//                     }
//                     else {
//                         yloc -= yIncr;
//                     }
//                     break; 
//                 //Forward NorthEast
//                 case NORTHEAST: 
//                 	if ((xloc + xIncr + imgWidth) >= width) {
//                         dir = Direction.NORTHWEST;   
//                     }
//                     else if ((yloc - yIncr) <= 0) {
//                         dir = Direction.SOUTHEAST; 
//                     }
//                     else {
//                         xloc += xIncr;
//                         yloc -= yIncr;
//                     }
//                     break; 
//                 //Forward NorthWest   
//                 case NORTHWEST: 
//                 	if ((xloc - xIncr) <= 0) {
//                         dir = Direction.NORTHEAST;
//                     }
//                     else if ((yloc - yIncr) <= 0) {
//                         dir = Direction.SOUTHWEST;
//                     }
//                     else {
//                         xloc -= xIncr;
//                         yloc -= yIncr;
//                     }
//                     break; 
//                 //Forward South
//                 case SOUTH: 
//                 	if ((yloc + yIncr + imgHeight) >= height) {
//                         dir = Direction.NORTH; 
//                     }
//                     else {
//                         yloc += yIncr;
//                     }
//                     break; 
//                 //Forward SouthEast
//                 case SOUTHEAST: 
//                 	if ((xloc + xIncr + imgWidth) >= width) {
//                         dir = Direction.SOUTHWEST;
//                     }
//                     else if ((yloc + yIncr + imgHeight) >= height) {
//                         dir = Direction.NORTHEAST; 
//                     }
//                     else {
//                         xloc += xIncr;
//                         yloc += yIncr;
//                     }
//                     break; 
//                 //Forward SouthWest
//                 case SOUTHWEST: 
//                 	if ((xloc - xIncr) <= 0) {
//                         dir = Direction.SOUTHEAST;
//                     }
//                     else if ((yloc + yIncr + imgHeight) >= height) {
//                         dir = Direction.NORTHWEST;
//                     }
//                     else {
//                         xloc -= xIncr;
//                         yloc += yIncr;
//                     }
//                     break;
//                 //Forward West
//                 case WEST: 
//                 	if ((xloc - xIncr) <= 0) {
//                         dir = Direction.EAST;
//                     }
//                     else {
//                         xloc -= xIncr;
//                     }
//                     break;
//          }
            
    }
    
    public int getX(){
        return xloc;
    }
    public int getY(){
        return yloc;
    }
    public Direction getDirection(){
        return dir;
    }
    
}
