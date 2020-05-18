import javafx.application.Application;
import javafx.stage.Stage;
import javafx.animation.AnimationTimer;

/** 
* This is the controller component of the MVS software design pattern.
* It acts as an interface between Model and View components to process all the business logic and incoming requests, manipulate data using the Model component and interact with the View to render the final output
    * @author Shane Cincotta 
*/

public class Controller extends Application {
	//data fields hold Model and View
	private Model model;
	private View view;

	     /** 
* Launches the controller
    * @param args 
*/

    public static void main(String[] args) {
        launch(args);
    }

    	     /** 
* The main entry point for all JavaFX applications. Called after the init method has returned, and after the system is ready for the application to begin running.
    * @param thestage A top-level container that hosts a Scene, which consists of visual elements 
*/

    @Override
	public void start(Stage theStage) {
        view = new View(theStage);
		model = new Model(view.getWidth(), view.getHeight(), 
                view.getImageWidth(), view.getImageHeight());
        


        new AnimationTimer() {

            public void handle(long currentNanoTime)
            {
                //increment the x and y coordinates, alter direction if necessary
                model.updateLocationandDirection();
                
                //input the x coordinates, y coordinates, and direction picture
                view.update(model.getX(), model.getY(), model.getDirection());
				   /** 
				* Exception handler
				    * @throws InterruptedException When a thread is waiting, sleeping, or otherwise occupied, and the thread is interrupted, either before or during the activity
				*/
                try {
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }.start();
        theStage.show();
    }

}
