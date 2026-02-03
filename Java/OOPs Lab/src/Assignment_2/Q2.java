package Assignment_2;

import java.util.Scanner;

class Garments {
    private String GCode;
    private String GType;
    private int GSize;
    private String GFabric;
    private float GPrice;
    public Garments() {
        GCode = GType = GFabric = "NA";
        GSize = 0;
        GPrice = 0;
    }
    private void Assign(){
        if(GType.equals("Trouser")) GPrice = 1300;
        else if(GType.equals("Shirt")) GPrice = 1100;

        if(!GFabric.equals("COTTON")) GPrice *= 0.9;
    }
    public void SetValue(String C, String T, int S, String F){
        GCode = C;
        GType = T;
        GSize = S;
        GFabric = F;
        Assign();
    }
    public void Display(){
        System.out.println("\nGarments:-");
        System.out.printf("GCode: %s\n",GCode);
        System.out.printf("GType: %s\n",GType);
        System.out.printf("GSize: %s\n",GSize);
        System.out.printf("GFabric: %s\n",GFabric);
        System.out.printf("GPrice: %s\n",GPrice);
    }
}

public class Q2 {
    public static void main(String[] args) {
        System.out.println();
        Scanner sc = new Scanner(System.in);
        Garments G = new Garments();
        System.out.printf("Enter Garment Code: ");
        String C = sc.next();
        System.out.printf("\nEnter Garment Type: ");
        String T = sc.next();
        System.out.printf("\nEnter Garment Size: ");
        int S = sc.nextInt();
        System.out.printf("\nEnter Garment Fabric: ");
        String F = sc.next();
        G.SetValue(C, T, S, F);
        G.Display();
    }
}
