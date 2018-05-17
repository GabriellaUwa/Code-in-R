/***
 * Gabriella Uwadiegwu
 * 05/11/2018
 *  
 * IT ISN'T IDEAL TO PUT DIFFERENT CLASSES THE SAME FILE... ESPECIALLY WITH JAVA
 * THIS IS SOLELY DONE BASED ON THE PROJECT REQUIREMENTS. WILL UPDATE IN THE FUTURE.
 *
 * This is a GUI representation of a Graph
 * User can create a graph and find its shortest path.
 * Clone or copy-paste for a test ride!
 * 
 * ***/

import javafx.scene.canvas.GraphicsContext;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.*;
import javafx.stage.Stage;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.collections.ObservableList;
import javafx.collections.FXCollections;
import javafx.scene.canvas.Canvas;
import javafx.scene.paint.Color;
import java.util.Random;
import java.util.Stack;

public class GGUwadiegwu extends Application {

    /***
     * List out of buttons in GUI
     * **/
    public static final ObservableList names = FXCollections.observableArrayList();

    /***
     * GUI and Events
     ***/
    @Override
    public void start(Stage stage) {

        HBox root = new HBox();
        StackPane background = new StackPane();

        Canvas canvas = new Canvas(850, 900);
        GraphicsContext gc = canvas.getGraphicsContext2D();
        
        ToggleGroup group = new ToggleGroup();
        Scene scene = new Scene(root, 1200, 900);

        RadioButton button1 = new RadioButton(" Add Vertex ");
        button1.setToggleGroup(group);

        RadioButton button2 = new RadioButton(" Add Edge ");
        button2.setToggleGroup(group);

        RadioButton button3 = new RadioButton(" Edge Endpoints ");
        button3.setToggleGroup(group);

        Button btn1 = new Button();
        btn1.setText("Add all edges");

        Button btn2 = new Button();
        btn2.setText("Help");

        Button btn3 = new Button();
        btn3.setText("Shortest Path");
        
        background.setStyle("-fx-background-color: DARKCYAN");

        stage.setScene(scene);
        stage.setTitle("Matrix Graph GUI");

        final ListView listView = new ListView();
        listView.setPrefSize(350, 400);

        TextField text = new TextField();
        text.clear();

        GridPane grid = new GridPane();
        grid.add(new Label("Weight: "), 0, 0);
        grid.add(text, 1, 0);

        names.addAll(
                button1, button2, button3,grid,"You must input weight before adding edge", btn1,btn3,btn2,"The minimum cost, for each vertex of the graph, from",
                "a vertex to all other vertices shall be displayed on a", "dialog box"
        );

        listView.setItems(names);

        /***
         * Instance of Graph class to be used for Application
         * +
         * Other needed containers
         * **/
        Graph<String> graph = new Graph<>(10);
        VCoord[] vcoord = new VCoord[1];
        VCoord[] vertexCoords = new VCoord[20];
        Stack<VCoord> temp = new Stack<>();

        /***
         * Adds all edges to each other. i.e. a complete graph
         * **/
        btn1.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                button2.setSelected(false);
                button3.setSelected(false);
                button1.setSelected(false);
               try{
                   graph.addAllEdges();
                   gc.setLineWidth(0.5);
                   double x_avg, y_avg; int w;

                   for(int i = 0; i<graph.numOfVertices; i++){
                       for(int j = 1; j< graph.numOfVertices; j++) {
                           if (graph.adjacencyMatrix[i][j] != Integer.MAX_VALUE && graph.adjacencyMatrix[j][i] != Integer.MAX_VALUE) {
                               gc.strokeLine(graph.vertexCoord[i].x + 5.5, graph.vertexCoord[i].y,graph.vertexCoord[j].x + 5.5, graph.vertexCoord[j].y);
                               w = (int) graph.adjacencyMatrix[i][j];
                               x_avg = ((graph.vertexCoord[i].x + graph.vertexCoord[j].x) / 2) + 4;
                               y_avg = ((graph.vertexCoord[i].y + graph.vertexCoord[j].y) / 2) + 4;
                               gc.fillText(Integer.toString(w), x_avg, y_avg);
                           }
                       }
                   }
               }
               catch (Exception e){}
            }
        });
        
        /****
         * Help Guide Button
         *****/
        btn2.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {

                ButtonType one = new ButtonType("Cancel", ButtonBar.ButtonData.CANCEL_CLOSE);
                Alert alert = new Alert(Alert.AlertType.NONE, "", one);
                alert.setWidth(500);
                alert.setHeight(500);
                DialogPane p = new DialogPane();
                p.setPrefSize(900,800);
                alert.setDialogPane(p);
                String s = "Welcome to the guide! Follow the steps below to test the application:\n\n" +
                        "1) First Select the add vertex radio button and place vertices as you please on the drawing interface" +
                        "\n2)To add edges between vertice, click the edge endpoints radio button and click the center of the first vertex" +
                        " and the second vertex you're trying to create an edge on. Do not click your mouse again on the canvas after this " +
                        "\n3)Now input a number on the \"weight\" text field"+
                        "\n4)Then click the add edge radio button and press the mouse on the canvas to show edge" +
                        "\n5)Repeat procedure, by choosing edge endpoints, inputing weights before adding edges"+
                        "\n6)The \"add all edge\"button make a complete graph with random weights, if you're lazy to go through these step" +
                        "\n7)The graph is limited to 10 vertices. " +
                        "\n8) The farther you set vertices apart the more visible the weights, Enjoy the App!";
                p.setContentText(s);
                p.getButtonTypes().add(one);
                alert.setHeaderText("Help Guide");
                alert.setResizable(true);
                alert.show();
            }
        });

        /****
         * Shortest Path Button
         ****/
        btn3.setOnAction(new EventHandler<ActionEvent>() {
            @Override
            public void handle(ActionEvent event) {
                    button2.setSelected(false);
                    button3.setSelected(false);
                    button1.setSelected(false);

                    ButtonType one = new ButtonType("Cancel", ButtonBar.ButtonData.CANCEL_CLOSE);
                    Alert alert = new Alert(Alert.AlertType.NONE, "", one);
                    alert.setWidth(100);
                    alert.setHeight(500);
                    DialogPane p = new DialogPane();
                    p.setPrefSize(300,1000);
                    alert.setDialogPane(p);

                    double t = 50;
                    String s = "";
                    for(int i = 0; i < graph.numOfVertices; i++) {
                        graph.shortestPath("v" + Integer.toString(i+1));
                        int j = 0;
                        while(j < graph.counter) {
                            s+=graph.costings.peek()+"\n";
                            graph.costings.pop();
                            t += 12;
                            j++;
                        }
                    }
                    p.setContentText(s);
                    p.getButtonTypes().add(one);
                    alert.setHeaderText("Minimum costings");
                    alert.setResizable(true);
                    alert.show();
            }
        });

        /****
         * Canvas event handling mouse events
         *****/
        canvas.addEventHandler(MouseEvent.MOUSE_PRESSED,
                new EventHandler<MouseEvent>() {
                    @Override

                    public void handle(MouseEvent e) {

                        if (button1.isSelected()) {
                            button2.setSelected(false);
                            button3.setSelected(false);

                            int x = (int) e.getX();
                            int y = (int) e.getY();
                            gc.setFill(Color.BLACK);
                            gc.fillOval(x, y, 12, 12);
                            
                            vcoord[0] = new VCoord(x, y);
                            for (int i = 0; i < vertexCoords.length; i++) {
                                if (vertexCoords[i] == null) {
                                    vertexCoords[i] = vcoord[0];
                                    try {
                                        String vname = "v" + Integer.toString(i+1);
                                        gc.fillText(vname, x -20,y+5);
                                        graph.addVertex(vname, vertexCoords[i]);
                                    } catch (Exception e1) {/**/}
                                    break;
                                }

                            }
                        }

                        if (button2.isSelected()) {

                            button1.setSelected(false);
                            button3.setSelected(false);
                            try {
                                VCoord one = temp.pop();
                                VCoord two = temp.pop();
                                int r = Integer.parseInt(text.getText());
                                graph.addEdge(graph.getCoordVertex(one), graph.getCoordVertex(two), r);
                                gc.setLineWidth(0.5);
                                gc.strokeLine(one.x, one.y, two.x, two.y);
                                double x_avg = ((one.x + two.x) /2) +4;
                                double y_avg = (one.y + two.y)/2 + 4;
                                gc.fillText(Integer.toString(r), x_avg, y_avg);

                            }catch (Exception e1){}
                        }
                        if (button3.isSelected()) {

                            button2.setSelected(false);
                            button1.setSelected(false);

                            int x = (int) e.getX();
                            int y = (int) e.getY();
                            vcoord[0] = new VCoord(x,y);

                            if(graph.getCoordIndex(vcoord[0]) != -1)
                                temp.push(vcoord[0]);
                        }
                    }
                });
        background.getChildren().add(canvas);
        root.getChildren().add(listView);
        root.getChildren().add(background);
        scene.setRoot(root);
        stage.show();
    }

    /***
     * Main to launch the above Javafx Application
     * **/

    public static void main(String[] args) {
        launch(args);
    }

    /***
     * VCoord class to keep track of coordinates of vertices in the GUI
     * **/
    private class VCoord{

        final double x;
        final double y;
        VCoord(double x, double y) {
            this.x=x;
            this.y=y;
        }
    }

    /**
     * Graph Class, Adjacency  Matrix Implementation
     * **/
    private class Graph<T> {

        int counter;
        int vertexCount;
        int numOfVertices;//indexes for vertices
        int numOfEdges;
        VCoord[] vertexCoord;//indexes for vertex coordinates in GUI. Matches vertices[]
        double[][] adjacencyMatrix; //to hold edge weight
        T[] vertices; //vertices
        boolean[] visited; //visitations

        Random rand = new Random();
        Stack<String> costings = new Stack<>();

        public Graph(int vertexCount) {

            this.vertexCount = vertexCount;
            numOfVertices = 0;
            numOfEdges = 0;
            adjacencyMatrix = new double[vertexCount][vertexCount];
            vertices = (T[]) new Object[vertexCount];
            vertexCoord = new VCoord[vertexCount];
            visited = new boolean[vertexCount];
            for (int i = 0; i < vertexCount; i++) {
                for (int j = 0; j < vertexCount; ++j) {
                    adjacencyMatrix[i][j] = Integer.MAX_VALUE;
                    adjacencyMatrix[j][i] = Integer.MAX_VALUE;
                }
            }
        }

        /*****
         Adds vertex to matrix. Undirected graph
         ******/
        public void addVertex(T item, VCoord v) throws Exception {

            if (isFull())
                throw new Exception("Graph is full. Cannot add.");
            if (isVertex(item)) {
                throw new Exception("Vertex already Exists");
            }
            if (numOfVertices >= 0 && numOfVertices < vertexCount) {
                vertices[numOfVertices] = item;
                vertexCoord[numOfVertices] = v;
                numOfVertices++;
            }
        }

        /*****
         Removes vertex from graph. NOT USED but utility
         ******/
        public void removeVertex(T item) throws Exception {

            if (isEmpty())
                throw new Exception("Graph is Empty. Cannot remove vertex");
            int n = getIndex(item);
            if (isVertex(item)) {

                for (int i = n; i < numOfVertices; i++) {
                    vertices[i] = vertices[i + 1];
                    vertexCoord[i] = vertexCoord[i + 1];
                }
                numOfVertices--;

                for (int i = n; i < numOfEdges; i++) {
                    for (int j = 0; j < numOfVertices; j++) {
                        adjacencyMatrix[i][j] = adjacencyMatrix[i + 1][j];
                    }
                }
                for (int i = n; i < numOfEdges; i++) {
                    for (int j = 0; j < numOfVertices; j++) {
                        adjacencyMatrix[j][i] = adjacencyMatrix[j][i + 1];
                    }
                }
                numOfEdges--;
            } else
                throw new Exception("Vertex not found to remove");
        }

        /*****
         Removes edge from graph. NOT USED but utility
         ******/
        public void removeEdge(T i, T j) {

            if (isVertex(i) && isVertex(j) & isEdge(i,j)) {
                adjacencyMatrix[getIndex(i)][getIndex(j)] = Integer.MAX_VALUE;
                adjacencyMatrix[getIndex(j)][getIndex(i)] = Integer.MAX_VALUE;
                numOfEdges--;
            }
        }
        /*****
         Gets the vertex of the coordinate in the GUI
         ******/
        public T getCoordVertex(VCoord v){

            for(int i = 0; i <vertexCoord.length; i++){
                if(getCoordIndex(vertexCoord[i]) == getCoordIndex(v)){
                    return vertices[i];
                }
            }
            return null;
        }

        /*****
         Adds an edge to the graph
         ******/
        public void addEdge(T i, T j, int w) throws Exception {

            if (isVertex(i) && isVertex(j) && getIndex(i) != getIndex(j) && !isEdge(i,j)) {
                adjacencyMatrix[getIndex(i)][getIndex(j)] = w;
                adjacencyMatrix[getIndex(j)][getIndex(i)] = w;
                numOfEdges++;
            } else
                throw new Exception("cannot add cost to the same origin or vertex is wrong. Check input");
        }

        /*****
         Adds all edge to vertices in the graph
         ******/
        public void addAllEdges() throws Exception {

            if(isEmpty())
                throw new Exception("No vertices to add edges");
            for(int i = 0; i <numOfVertices; i++) {
                for (int j = 1; j < numOfVertices; j++) {
                    if (isVertex(vertices[i]) && isVertex(vertices[j]) && i != j && !isEdge(vertices[i], vertices[j])) {
                        adjacencyMatrix[i][j] = rand.nextInt(10) + 1;
                        adjacencyMatrix[j][i] = adjacencyMatrix[i][j];
                        numOfEdges++;
                    }
                }
            }
        }

        /*****
         Checks if two vertices are connected
         ******/
        public boolean isEdge(T i, T j) {

            if (i == j)
                return false;
            int r = getIndex(i); //index
            int c = getIndex(j); //index

            if (r == -1 || c == -1)
                return false;

            return (adjacencyMatrix[r][c] != Integer.MAX_VALUE &&
                    adjacencyMatrix[c][r] != Integer.MAX_VALUE);
        }

        /*****
         Checks if graph is empty
         ******/
        public boolean isEmpty() {
            return numOfVertices == 0;
        }

        /*****
         checks if graph is full
         ******/
        public boolean isFull() {

            return numOfVertices == vertexCount;
        }

        /*****
         Checks if some label is part of the graph
         ******/
        public boolean isVertex(T item) {

            for (int i = 0; i < vertexCount; i++) {
                if (vertices[i] == item)
                    return true;
            }
            return false;
        }

        public int getCoordIndex(VCoord c){

            for (int i = 0; i < numOfVertices; i++) {
                if (Math.abs(vertexCoord[i].x - c.x) <=10.0 && Math.abs(vertexCoord[i].y - c.y) <= 10.0)
                    return i;
            }
            return -1;
        }

        /*****
         gets the index of a vertex
         ******/
        public int getIndex(T item) {

            for (int i = 0; i < numOfVertices; i++) {
                if (vertices[i].equals(item))
                    return i;
            }
            return -1;
        }

        /*****
         Returns the weight of an edge. NOT USED but utility
         ***/

        public double edgeWeight(T i, T j) {

            int a = getIndex(i);
            int b = getIndex(j);
            return adjacencyMatrix[a][b];
        }

        /*****
         Visits a vertex in the graph
         ******/
        public void Visit(T item) throws Exception {

            if (isVertex(item))
                visited[getIndex(item)] = true;
            else
                throw new Exception("Item is not there to visit");
        }

        /*****
         Checks if a vertex is visited
         ******/
        public boolean isVisited(T item) throws Exception {

            if (!isVertex(item))
                throw new Exception("vertex is not part of graph");
            int n = getIndex(item);
            return visited[n];
        }

        /*****
         Clears all visitations to graphs
         ******/
        public void clearVisited() {

            for (int i = 0; i < vertexCount; i++)
                visited[i] = false;
        }

        /*****
         Returns the vertex at a give index
         ******/
        public T get_vertex(int index) {
            return vertices[index];
        }

        /*****
         Returns a Stack of shortest path to and from all vertices to the other
         ******/
        public Stack<String> shortestPath(T v){

            double[] cost = new double[30];
            int index_Item = getIndex(v);
            clearVisited();
            try{
            Visit(v);
            }catch (Exception e){}
            cost[index_Item] = Integer.MAX_VALUE;

            for (int i = 0; i < vertexCount; i++)
                cost[i] = adjacencyMatrix[index_Item][i];

            for (int i = 0; i < numOfVertices - 1; i++) {

                int min = Integer.MAX_VALUE;
                int index = 0;

                T t;
                for (int j = 0; j < numOfVertices; j++) {
                    t = get_vertex(j);
                    try {
                        if (!isVisited(t) && cost[j] <= min) {
                            min = (int) cost[j];
                            index = j;
                        }
                    }catch(Exception e){}
                }

                visited[index] = true;
                for (int w = 0; w < numOfVertices; w++) {
                    if (!visited[w]) {
                        if (cost[w] > Math.abs(adjacencyMatrix[index][w]) + min) {
                            cost[w] = Math.abs(adjacencyMatrix[index][w]) + min;
                        }
                    }
                }
            }
            counter = 0;
            for (int k = 0; k < numOfVertices; k++) {
                int n = getIndex(v);
                if ((k != n) && (cost[k] != 0.0)) {
                    costings.push("Cost from " + v + " to " + vertices[k] + " is " + Integer.toString((int) cost[k]) + " ");
                    counter++;
                }
            }
            return costings;
        }
    }
}
