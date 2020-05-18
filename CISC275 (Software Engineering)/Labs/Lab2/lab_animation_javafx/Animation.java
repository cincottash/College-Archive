//T Harvey
// Loosely based on https://github.com/tutsplus/Introduction-to-JavaFX-for-Game-Development/blob/master/Example3.java 

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
    final double xIncr = 8;
    final double yIncr = 2;
    final static int canvasWidth = 500;
    final static int canvasHeight = 300;
    final static int imgWidth = 165;
    final static int imgHeight = 165;

    // TODO: Change the code so that at least eight orc animation pngs are loaded

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
        Image orc_img = createImage();

        final long startNanoTime = System.nanoTime();

        new AnimationTimer() {
            public void handle(long currentNanoTime)
            {
                double t = (currentNanoTime - startNanoTime) / 1e9; 

                xloc += xIncr;
                yloc += yIncr;

                // Clear the canvas
                gc.clearRect(0, 0, canvasWidth, canvasHeight);

                // draw the subimage from the original png to animate the orc's motion
                gc.drawImage(orc_img, imgWidth*picInd, 0, imgWidth, imgHeight,
                                    xloc, yloc, imgWidth, imgHeight);
                picInd = (picInd + 1) % canvasCount;
                
                try {
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                
                // TODO: Keep the orc from walking off-screen, turn around when bouncing off walls.
                //Be sure that animation picture direction matches what is happening on screen.
            }
        }.start();
        theStage.show();
    }

    //Read image from file and return
    private Image createImage() {
        Image img = new Image("images/orc/orc_forward_southeast.png");
        return img;   	
    	// TODO: Change this method so you can load other orc animation bitmaps
    }
}


