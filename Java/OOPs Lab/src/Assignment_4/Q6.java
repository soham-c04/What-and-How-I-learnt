package Assignment_4;

import java.time.LocalDate;
import java.util.*;

class User {
    private String userId;
    private String password;
    private String loginStatus;
    private LocalDate registerDate;

    public User(String userId) {
        this.userId = userId;
        this.loginStatus = "LoggedOut";
        this.registerDate = LocalDate.now();
    }

    public String getUserId() {
        return userId;
    }

    public void setPassword(String pwd) {
        this.password = pwd;
    }

    public boolean verifyLogin(String pwd) {
        boolean ok = pwd != null && pwd.equals(password);
        if (ok) loginStatus = "LoggedIn";
        return ok;
    }

    public String getLoginStatus() {
        return loginStatus;
    }

    public LocalDate getRegisterDate() {
        return registerDate;
    }
}

class Customer extends User {   // Inheritance
    private String customerName;
    private String address;
    private String email;
    private String creditCardInfo;
    private String shippingInfo;
    private float accountBalance;

    // Composition - 0 or more ShoppingCarts
    private List<ShoppingCart> shoppingCarts;
    // Composition - 0 or more Orders;
    private List<Order> orders;

    public Customer(String userId, String customerName, String address, String email, String creditCardInfo, float accountBalance) {
        super(userId);
        this.customerName = customerName;
        this.address = address;
        this.email = email;
        this.creditCardInfo = creditCardInfo;
        this.accountBalance = accountBalance;
        this.shoppingCarts = new ArrayList<>();
        this.orders = new ArrayList<>();
    }

    public void register() {
        System.out.println("Customer " + customerName + " registered with email " + email + " on " + getRegisterDate());
    }

    public boolean login(String pwd) {
        boolean ok = verifyLogin(pwd);
        System.out.println(ok ? "Login success" : "Login failed");
        return ok;
    }

    public void updateProfile(String name, String addr, String em, String cc) {
        this.customerName = name;
        this.address = addr;
        this.email = em;
        this.creditCardInfo = cc;
        System.out.println("Profile updated for " + customerName);
    }

    public void addShoppingCart(ShoppingCart cart) {
        shoppingCarts.add(cart);
        cart.setOwner(this);
        System.out.println("ShoppingCart added for customer " + customerName + " (Cart ID: " + cart.getCartId() + ")");
    }

    public void addOrder(Order order) {
        orders.add(order);
        System.out.println("Order " + order.getOrderId() + " added to customer " + customerName);
    }

    public String getCustomerName() { return customerName; }
    public String getAddress() { return address; }
    public String getEmail() { return email; }
    public String getCreditCardInfo() { return creditCardInfo; }
    public float getAccountBalance() { return accountBalance; }
    public List<ShoppingCart> getShoppingCarts() { return shoppingCarts; }
    public List<Order> getOrders() { return orders; }
}

class Administrator extends User {  // Inheritance from User
    private String adminName;
    private String email;

    public Administrator(String userId, String email, String adminName) {
        super(userId);
        this.email = email;
        this.adminName = adminName;
    }

    public String getAdminName() {
        return adminName;
    }

    public boolean updateCatalog() {
        System.out.println("Catalog updated by " + adminName);
        return true;
    }
}

class ShoppingCart {
    private static int nextId = 1;
    private final int cartId;
    private List<CartItem> items;

    // Composition - Exactly 1 owner
    private Customer owner;

    public ShoppingCart() {
        this.cartId = nextId++;
        this.items = new ArrayList<>();
    }

    public int getCartId() {
        return cartId;
    }

    public void setOwner(Customer c) { this.owner = c; }

    public void addCartItem(int productId, String productName, int quantity, double unitCost) {
        for (CartItem it : items) {
            if (it.productId == productId) {
                it.quantity += quantity;
                it.subTotal = it.quantity * it.unitCost;
                System.out.println("Updated quantity for product " + productName + " to " + it.quantity);
                return;
            }
        }
        CartItem newItem = new CartItem(productId, productName, quantity, unitCost);
        items.add(newItem);
        System.out.println("Added " + quantity + " x " + productName + " to cart " + cartId);
    }

    public void updateQuantity(int productId, int newQty) {
        for (CartItem it : items) {
            if (it.productId == productId) {
                it.quantity = newQty;
                it.subTotal = it.quantity * it.unitCost;
                System.out.println("Quantity updated for product " + productId + " to " + newQty);
                return;
            }
        }
        System.out.println("Product not found in cart.");
    }

    public void viewCartDetails() {
        System.out.println("Cart ID: " + cartId + " - Items:");
        if (items.isEmpty()) {
            System.out.println("  (empty)");
            return;
        }
        for (CartItem it : items) {
            System.out.printf("  Product %d | %s | qty=%d | unit=%.2f | subtotal=%.2f%n",
                    it.productId, it.productName, it.quantity, it.unitCost, it.subTotal);
        }
    }

    public Order checkOut(Customer customer) {
        if (items.isEmpty()) {
            System.out.println("Cannot checkout empty cart.");
            return null;
        }
        double total = 0.0;
        int productId = items.get(0).productId;
        String productName = items.get(0).productName;
        int quantity = 0;
        double unitCost = items.get(0).unitCost;
        for (CartItem it : items) {
            total += it.subTotal;
            quantity += it.quantity;
        }

        OrderDetails od = new OrderDetails(0, productId, productName, quantity, unitCost);
        od.calPrice();

        Order order = new Order(customer.getCustomerName(), customer.getUserId(), od);
        order.setTotalAmount(total);
        System.out.println("Checkout complete. Created Order ID: " + order.getOrderId());
        items.clear();
        return order;
    }

    private static class CartItem {
        int productId;
        String productName;
        int quantity;
        double unitCost;
        double subTotal;

        CartItem(int productId, String productName, int quantity, double unitCost) {
            this.productId = productId;
            this.productName = productName;
            this.quantity = quantity;
            this.unitCost = unitCost;
            this.subTotal = quantity * unitCost;
        }
    }
}

class Order {
    private static int nextOrderId = 1;
    private int orderId;
    private LocalDate dateCreated;
    private LocalDate dateShipped;
    private String customerName;
    private String status;
    private int shippingId;
    private double totalAmount;

    // Composition - Exactly 1 customer for each Order.
    private String customerId;
    // Composition - 1:1 with ShippingInfo and OrderDetails.
    private ShippingInfo shippingInfo;
    private OrderDetails orderDetails;

    public Order(String customerName, String customerId, OrderDetails details) {
        this.orderId = nextOrderId++;
        this.dateCreated = LocalDate.now();
        this.customerName = customerName;
        this.customerId = customerId;
        this.status = "Created";
        this.orderDetails = details;
        this.orderDetails.setOrderId(this.orderId);
    }

    public int getOrderId() {
        return orderId;
    }

    public void setShippingInfo(ShippingInfo info) {
        this.shippingInfo = info;
        this.shippingId = info.getShippingId();
    }

    public void placeOrder() {
        if (orderDetails != null) orderDetails.calPrice();
        this.status = "Placed";
        System.out.println("Order " + orderId + " placed for customer " + customerName);
    }

    public void markShipped(LocalDate shippedDate) {
        this.dateShipped = shippedDate;
        this.status = "Shipped";
        System.out.println("Order " + orderId + " shipped on " + dateShipped);
    }

    public void setTotalAmount(double totalAmount) {
        this.totalAmount = totalAmount;
    }

    public OrderDetails getOrderDetails() { return orderDetails; }
    public ShippingInfo getShippingInfo() { return shippingInfo; }
    public String getStatus() { return status; }
    public double getTotalAmount() { return totalAmount; }
}

class ShippingInfo {
    private static int nextShipId = 1;
    private int shippingId;
    private String shippingType;
    private double shippingCost;
    private int shippingRegionId;

    public ShippingInfo(String shippingType, double shippingCost, int regionId) {
        this.shippingId = nextShipId++;
        this.shippingType = shippingType;
        this.shippingCost = shippingCost;
        this.shippingRegionId = regionId;
    }

    public int getShippingId() {
        return shippingId;
    }

    public void updateShippingInfo(String type, double cost, int regionId) {
        this.shippingType = type;
        this.shippingCost = cost;
        this.shippingRegionId = regionId;
        System.out.println("Shipping info updated: " + type + " cost=" + cost);
    }

    public String getShippingType() { return shippingType; }
    public double getShippingCost() { return shippingCost; }
    public int getShippingRegionId() { return shippingRegionId; }
}

class OrderDetails {
    private int productId;
    private String productName;
    private int quantity;
    private double unitCost;
    private double subTotal;

    // Composition - 1:1 with Order.
    private int orderId;

    public OrderDetails(int orderId, int productId, String productName, int quantity, double unitCost) {
        this.orderId = orderId;
        this.productId = productId;
        this.productName = productName;
        this.quantity = quantity;
        this.unitCost = unitCost;
    }

    public void calPrice() {
        this.subTotal = this.quantity * this.unitCost;
        System.out.println("OrderDetails: product " + productName + " subtotal = " + subTotal);
    }

    public void setOrderId(int id) {
        this.orderId = id;
    }

    public double getSubTotal() { return subTotal; }
    public int getProductId() { return productId; }
    public int getQuantity() { return quantity; }
}

public class Q6 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        Administrator admin = new Administrator("soham_c04", "soham@iitbb.ac.in", "Soham");
        admin.setPassword("password");
        System.out.println("Admin created: " + admin.getAdminName());

        Customer customer = new Customer("1st", "goku", "BHR", "goku@db.com", "234567", 1000.0f);
        customer.setPassword("password2");
        customer.register();
        if (customer.login("password2")) {
            System.out.println(customer.getCustomerName() + " logged in successfully.");
        }

        ShoppingCart cart = new ShoppingCart();
        customer.addShoppingCart(cart);

        cart.addCartItem(1, "Shenron", 1, 199.0f);
        cart.addCartItem(2, "Porunga", 1, 999.0f);
        cart.viewCartDetails();

        Order order = cart.checkOut(customer);
        if (order != null) {
            ShippingInfo si = new ShippingInfo("Standard", 50, 1);
            order.setShippingInfo(si);

            order.placeOrder();
            customer.addOrder(order);
        }

        System.out.println("\n--- Customer Summary ---");
        System.out.println("Customer: " + customer.getCustomerName() + " (ID: " + customer.getUserId() + ")");
        System.out.println("Number of carts: " + customer.getShoppingCarts().size());
        System.out.println("Number of orders: " + customer.getOrders().size());

        sc.close();
    }
}