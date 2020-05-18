//T Harvey
// Loosely based on https://github.com/tutsplus/Introduction-to-JavaFX-for-Game-Development/blob/master/Example3.java 
import java.util.*;
import java.math.*;
import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.Group;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.image.Image;
import javafx.animation.AnimationTimer;

import java.io.IOException;
import java.io.File;

// Animation of Orc walking
public class Animation extends Application {
    final int canvasCount = 10;
    int picInd = 0;
    double xloc = 0;
    double yloc = 0;
    double xIncr = 6;
    double yIncr = 2;
    final static int canvasWidth = 500;
    final static int canvasHeight = 300;
    final static int imgWidth = 165;
    final static int imgHeight = 165;
    
    int flag0 = 1;
    int flag1 = 0;
    int flag2 = 0;
    int flag3 = 0;
    int flag4 = 0;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage theStage) {
        theStage.setTitle("Orc");

        Group root = new Group();
        Scene theScene = new Scene(root);
        theStage.setScene(theScene);

        Canvas canvas = new Canvas(canvasWidth, canvasHeight);
        root.getChildren().add(canvas);
        GraphicsContext gc = canvas.getGraphicsContext2D();
        
        //here is where we actually make the orc
        Image orc_img_north = createImage("orc_forward_north.png");
        Image orc_img_north_east = createImage("orc_forward_northeast.png");
        Image orc_img_north_west = createImage("orc_forward_northwest.png");
        Image orc_img_south = createImage("orc_forward_south.png");
        Image orc_img_south_east = createImage("orc_forward_southeast.png");
        Image orc_img_south_west = createImage("orc_forward_southwest.png");
        Image orc_img_east = createImage("orc_forward_east.png");
        Image orc_img_west = createImage("orc_forward_west.png");
        

        final long startNanoTime = System.nanoTime();

        new AnimationTimer() {
            public void handle(long currentNanoTime)
            {
                double t = (currentNanoTime - startNanoTime) / 1e9; 
  
                //for controlling the position
                //flag0 is our initial direction
                if(flag0 == 1) {                	                   
                	//System.out.println("flag0 set");
                	xloc += xIncr;
                	yloc += yIncr;
                	
                    // Clear the canvas
                    gc.clearRect(0, 0, canvasWidth, canvasHeight);

                    // draw the subimage from the original png to animate the orc's motion
                    gc.drawImage(orc_img_south_east, imgWidth*picInd, 0, imgWidth, imgHeight, xloc, yloc, imgWidth, imgHeight);
                    picInd = (picInd + 1) % canvasCount;
                    
                }
                
                //flag1 triggered when right edge is hit
                else if(flag1 == 1) {
                	//System.out.println("flag1 set");
                	
                	//x has to decrease
                	xloc += -xIncr;                	
                	//y can increase or decrease
                	yloc += yIncr;
                	
                    gc.clearRect(0, 0, canvasWidth, canvasHeight);
                    // draw the subimage from the original png to animate the orc's motion
                    gc.drawImage(orc_img_south_west, imgWidth*picInd, 0, imgWidth, imgHeight, xloc, yloc, imgWidth, imgHeight);
                    picInd = (picInd + 1) % canvasCount;


                }
                
                //flag2 is triggered when the left edge is hit
                else if(flag2 == 1) {
                	//System.out.println("flag2 set");
                	//x has to increase
                	xloc += xIncr;          
                	//y can increase or decrease
                	yloc += -yIncr;
                	
                    gc.clearRect(0, 0, canvasWidth, canvasHeight);
                    // draw the subimage from the original png to animate the orc's motion
                    gc.drawImage(orc_img_north_east, imgWidth*picInd, 0, imgWidth, imgHeight, xloc, yloc, imgWidth, imgHeight);
                    picInd = (picInd + 1) % canvasCount;
                	
                }
                
                //flag3 is triggered when the bottom edge is hit
                else if(flag3 == 1) {
                	//System.out.println("flag3 set");
                	
                	//x can increase or decrease
                	xloc += -xIncr;
                	//y has to decrease
                	yloc += -yIncr;
                	
                    gc.clearRect(0, 0, canvasWidth, canvasHeight);
                    // draw the subimage from the original png to animate the orc's motion
                    gc.drawImage(orc_img_north_west, imgWidth*picInd, 0, imgWidth, imgHeight, xloc, yloc, imgWidth, imgHeight);
                    picInd = (picInd + 1) % canvasCount;
                }
                
                //flag4 is triggered when the top edge is hit
                else if(flag4 == 1) {
                	//System.out.println("flag4 set");
                	
                	//x can increase or decrease
                	xloc += xIncr;
                	//y has to increase
                	yloc += yIncr;
                	
                    gc.clearRect(0, 0, canvasWidth, canvasHeight);
                    // draw the subimage from the original png to animate the orc's motion
                    gc.drawImage(orc_img_south_east, imgWidth*picInd, 0, imgWidth, imgHeight, xloc, yloc, imgWidth, imgHeight);
                    picInd = (picInd + 1) % canvasCount;
                }                
           
                               
                try {
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                               
                //System.out.println(xloc +" "+ yloc);
                
                //checking what edges we're at
                //hit right edge
                if((xloc >= canvasHeight) && (yloc <= canvasHeight - imgHeight)) {
                	//System.out.println("at right edge");
                	//reset the flags
                	flag0 = flag1 = flag2 = flag3 = flag4 = 0;
                	flag1 = 1;

                }
                //hit left edge
                else if((xloc <= 0) && (yloc <= canvasHeight - imgHeight)){
                	//System.out.println("at left edge");
                	flag0 = flag1 = flag2 = flag3 = flag4 = 0;
                	flag2 = 1;
                }
                //hit bottom edge
                else if((xloc < canvasHeight) && (yloc > canvasHeight - imgHeight)){
                	//System.out.println("at bottom edge");
                	flag0 = flag1 = flag2 = flag3 = flag4 = 0;
                	flag3 = 1;
                }
                //hit top edge
                else if((xloc <= canvasHeight) && (yloc <= 0)){
                	//System.out.println("at top edge");
                	flag0 = flag1 = flag2 = flag3 = flag4 = 0;
                	flag4 = 1;
                }
                
            }
        }.start();
        theStage.show();
    }

    //Read image from file and return
    private Image createImage(String fileName) {
        Image img = new Image("file:" + fileName);
        return img;   	
    }
    
}


