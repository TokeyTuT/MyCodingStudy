package www.tokeytut.user;

import java.util.ArrayList;

public final class UserData {
    private static final ArrayList<User> allUser = new ArrayList<>();

    static{
        allUser.add(new User("tokey","0805"));
    }
    //添加 user
    public static boolean addUser(String username,String pwd){
        if(findUser(username,pwd)){
            return false;
        }
        return allUser.add(new User(username,pwd));
    }

    //找是否存在 user
    public static boolean findUser(String username,String pwd){
        return findUser(new User(username,pwd));
    }
    public static boolean findUser(User u){
        for (User user : allUser) {
            if(u.getUsername().equals(user.getUsername())&& u.getPwd().equals(user.getPwd())){
                return true;
            }
        }
        return false;
    }
    public static boolean findUserName(String name){
        for(User u:allUser){
            if(u.getUsername().equals(name)) return true;
        }
        return false;
    }
    public static int getLength(){
        return allUser.size();
    }
    public static void printAllUser(){
        for(User u:allUser){
            System.out.println("[" + u.getUsername() + ","  + u.getPwd() + "]");
        }
    }
}
