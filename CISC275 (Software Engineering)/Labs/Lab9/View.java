import javafx.scene.image.Image;
//import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.Group;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
//import javafx.animation.AnimationTimer;
//import java.io.IOException;
//import java.io.File;
import javafx.scene.control.Button;
import javafx.event.EventHandler; 
import javafx.event.ActionEvent; 

class View{
	//represents the state of our button press, 0 = off, 1 = on
	int button = 0;
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
    
    //Read image from file and return
    private Image createImage(String fileName) {
        Image img = new Image("file:" + fileName);
        return img;   	
    }
    

    GraphicsContext gc;
    
    int canvasWidth = 500;
    int canvasHeight = 300;
    int imgWidth = 165;
    int imgHeight = 165;

	public View(Stage theStage) {
		theStage.setTitle("Orc");
		
		Button b = new Button("Start/Stop"); 

		EventHandler<ActionEvent> event = new EventHandler<ActionEvent>() { 
            public void handle(ActionEvent e) 
            { 
            	if(button == 0) {
            		button = 1;
            	}
            	
            	else {
            		button = 0;
            	}
            	//System.out.println(button);
               
            } 
        }; 
  
        // when button is pressed 
        b.setOnAction(event); 
        
        Group root = new Group();
        Scene theScene = new Scene(root);
        theStage.setScene(theScene);

        Canvas canvas = new Canvas(canvasWidth, canvasHeight);
        root.getChildren().add(canvas);
        root.getChildren().add(b);
        b.setOnAction(event); 
        gc = canvas.getGraphicsContext2D();

	}
	
	//input the x coordinates, y coordinates, and direction picture
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
	
	public int getWidth() {
		return canvasWidth;
	}
	public int getHeight() {
		return canvasHeight;
	}
	public int getImageWidth() {
		return imgWidth;
	}
	public int getImageHeight() {
		return imgHeight;
	}

	public int getButtonState() {
		return button;
	}
	
}