package Assignment_3;

import java.util.Scanner;

import static java.lang.Math.acos;
import static java.lang.Math.sqrt;

abstract class Object3D {
    abstract protected double SurfaceArea();
    abstract protected double Volume();
}

class Box extends Object3D {
    private int length;
    private int width;
    private int height;
    public Box(int length, int width, int height) {
        this.length = length;
        this.width = width;
        this.height = height;
    }
    @Override
    public double SurfaceArea() {
        return 2*(length*width + width*height + height*length);
    }
    @Override
    public double Volume() {
        return length*width*height;
    }
}

class Cube extends Box{
    public Cube(int side){
        super(side,side,side);
    }
}

class Cylinder extends Object3D {
    private static final double PI = 2*acos(0);
    private int height;
    private int radius;
    public Cylinder(int height, int radius){
        this.height = height;
        this.radius = radius;
    }
    @Override
    public double SurfaceArea() {
        return 2*PI*radius*(radius+height);
    }
    @Override
    public double Volume() {
        return PI*radius*radius*height;
    }
}

class Cone extends Object3D {
    private static double PI = 2*acos(0);
    private int height;
    private int radius;
    public Cone(int height, int radius){
        this.height = height;
        this.radius = radius;
    }
    @Override
    public double SurfaceArea() {
        return PI*radius*(radius+sqrt(height*height + radius*radius));
    }
    @Override
    public double Volume() {
        return PI*radius*radius*height/3;
    }
}

public class Q3 {
    public static void main(String[] args){
        System.out.println();
        Scanner sc =  new Scanner(System.in);

        System.out.print("Enter Box Height: ");
        int height = sc.nextInt(); sc.nextLine();
        System.out.print("Enter Box Width: ");
        int width = sc.nextInt(); sc.nextLine();
        System.out.print("Enter Box Length: ");
        int length = sc.nextInt(); sc.nextLine();
        Box b =  new Box(height,width,length);
        System.out.println("\nBox:-");
        System.out.println("Surface Area: "+b.SurfaceArea());
        System.out.println("Volume: "+b.Volume());

        System.out.print("\nEnter cube side length: ");
        int side = sc.nextInt(); sc.nextLine();
        Cube c = new Cube(side);
        System.out.println("\nCube:-");
        System.out.println("Surface Area: "+c.SurfaceArea());
        System.out.println("Volume: "+c.Volume());

        System.out.print("\nEnter cylinder height: ");
        int height2 = sc.nextInt(); sc.nextLine();
        System.out.print("Enter cylinder radius: ");
        int radius = sc.nextInt(); sc.nextLine();
        Cylinder cy = new Cylinder(radius,height2);
        System.out.println("\nCylinder:-");
        System.out.println("Surface Area: "+cy.SurfaceArea());
        System.out.println("Volume: "+cy.Volume());

        System.out.print("\nEnter Cone height: ");
        int height3 = sc.nextInt(); sc.nextLine();
        System.out.print("Enter Cone radius: ");
        int radius2 = sc.nextInt(); sc.nextLine();
        Cone cone = new Cone(height3,radius2);
        System.out.println("\nCone:-");
        System.out.println("Surface Area: "+cone.SurfaceArea());
        System.out.println("Volume: "+cone.Volume());
    }
}
