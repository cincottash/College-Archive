import javafx.scene.image.Image;
//import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.Group;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
//At a minimum, all project files will have @author tags, and all project methods will have @param and @return
//tags.


 /** 
* This is the view component of the MVS software design pattern.
* It contains any representation of information such as a chart, diagram or table.
    * @author Shane Cincotta 
*/

public class View{
	int picInd = 0;
	final int canvasCount = 10;
    //here is where we actually make the orc
    Image orc_img_north = createImage("orc_forward_north.png");
    Image orc_img_north_east = createImage("orc_forward_northeast.png");
    Image orc_img_north_west = createImage("orc_forward_northwest.png");
    Image orc_img_south = createImage("orc_forward_south.png");
    Image orc_img_south_east = createImage("orc_forward_southeast.png");
    Image orc_img_south_west = createImage("orc_forward_southwest.png");
    Image orc_img_east = createImage("orc_forward_east.png");
    Image orc_img_west = createImage("orc_forward_west.png");
    

     /** 
* Read image from file and return
    * @param fileName The base file name to load from path
    * @return Returns the image file in the path of the file name
*/

    public Image createImage(String fileName) {
        Image img = new Image("file:" + fileName);
        return img;   	
    }
    

    GraphicsContext gc;
    
    int canvasWidth = 500;
    int canvasHeight = 300;
    int imgWidth = 165;
    int imgHeight = 165;


     /** 
*View constructor
    * @param theStage A top-level container that hosts a Scene, which consists of visual elements
    * @return Returns a new instance of the class
*/

	public View(Stage theStage) {
		theStage.setTitle("Orc");

        Group root = new Group();
        Scene theScene = new Scene(root);
        theStage.setScene(theScene);

        Canvas canvas = new Canvas(canvasWidth, canvasHeight);
        root.getChildren().add(canvas);
        gc = canvas.getGraphicsContext2D();

	}
	

	 /** 
*inputs the x coordinates, y coordinates, and direction picture
    * @param xloc x coordinate of the image
    * @param yloc y coordinate of the image
    * @param direction Direction the image is moving
*/

	public void update(double xloc, double yloc, String direction) {
		gc.clearRect(0, 0, canvasWidth, canvasHeight);
		
		switch(direction) {
			case "NORTH":
				gc.drawImage(orc_img_north, imgWidth*picInd, 0, imgWidth, imgHeight, xloc, yloc, imgWidth, imgHeight);
				break;
			case "NORTHEAST":
				gc.drawImage(orc_img_north_east, imgWidth*picInd, 0, imgWidth, imgHeight, xloc, yloc, imgWidth, imgHeight);
				break;
			case "EAST":
				gc.drawImage(orc_img_east, imgWidth*picInd, 0, imgWidth, imgHeight, xloc, yloc, imgWidth, imgHeight);
				break;
			case "SOUTHEAST":
				gc.drawImage(orc_img_south_east, imgWidth*picInd, 0, imgWidth, imgHeight, xloc, yloc, imgWidth, imgHeight);
				break;
			case "SOUTH":
				gc.drawImage(orc_img_south, imgWidth*picInd, 0, imgWidth, imgHeight, xloc, yloc, imgWidth, imgHeight);
				break;
			case "SOUTHWEST":
				gc.drawImage(orc_img_south_west, imgWidth*picInd, 0, imgWidth, imgHeight, xloc, yloc, imgWidth, imgHeight);
				break;
			case "WEST":
				gc.drawImage(orc_img_west, imgWidth*picInd, 0, imgWidth, imgHeight, xloc, yloc, imgWidth, imgHeight);
				break;
			case "NORTHWEST":
				gc.drawImage(orc_img_north_west, imgWidth*picInd, 0, imgWidth, imgHeight, xloc, yloc, imgWidth, imgHeight);
				break;
		}
		
       picInd = (picInd + 1) % canvasCount;
	}
	
	 /** 
*Gets the canvas width
    * @return Returns int canvas width
*/

	public int getWidth() {
		return canvasWidth;
	}

	/** 
*Gets the canvas height
    * @return Returns int canvas height
*/

	public int getHeight() {
		return canvasHeight;
	}

	 /** 
*Gets the image width
    * @return Returns int image width
*/


	public int getImageWidth() {
		return imgWidth;
	}

	/** 
*Gets the image height
    * @return Returns int image height
*/

	public int getImageHeight() {
		return imgHeight;
	}
	
	
	
}