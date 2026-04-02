package com.tokey.domain;

import java.util.Objects;

public class User {
    private String name = "";
    private String password = "";

    public User() {
    }

    public User(String name, String password) {
        this.name = name;
        this.password = password;
    }

    public String getName() {
        return name;
    }

    public String getPassword() {
        return password;
    }


    /**
     * 设置
     * @param name
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * 设置
     * @param password
     */
    public void setPassword(String password) {
        this.password = password;
    }

    public String toString() {
        return name;
    }

    @Override
    public boolean equals(Object o) {
        if(o == null || !(o instanceof User)) return false;
        User u = (User) o;
        return u.getName().equals(this.name) && u.password.equals(this.password);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name,password);
    }
}
