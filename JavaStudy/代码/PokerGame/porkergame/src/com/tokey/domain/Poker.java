package com.tokey.domain;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.util.ArrayList;

public class Poker extends JLabel implements MouseListener {
    private String name = null;
    private boolean canClick = false;
    private boolean up = false;
    private boolean isClicked = false;

    public Poker(String name, boolean up){
        this.name = name;
        this.up = up;

        if(up){
            turnFront();
        }
        else{
            turnRear();
        }
        //设置牌的宽高大小
        this.setSize(71, 96);
        //把牌显示出来
        this.setVisible(true);
        //给每一张牌添加鼠标监听
        this.addMouseListener(this);

    }

    public Poker() {
    }

    public Poker(String name, boolean canClick, boolean up, boolean isClicked) {
        this.name = name;
        this.canClick = canClick;
        this.up = up;
        this.isClicked = isClicked;
    }


    public void turnFront() {
        JLabel card = new JLabel(new ImageIcon("/Users/tuttokey/PokerGame/image/poker" + name + ".png"));
        up = true;
    }
    private void turnRear(){
        JLabel card = new JLabel(new ImageIcon("image/poker/rear.png"));
        up = false;
    }


    @Override
    public void mouseClicked(MouseEvent e) {
        if(canClick){
            Point from = this.getLocation();
            int step = 0;

            if(isClicked){
                step = -20;
            }else{
                step = 20;
            }

            Point to = new Point(from.x,from.y + step);
            this.setLocation(to);
            isClicked = !isClicked;
        }

    }

    @Override
    public void mousePressed(MouseEvent e) {

    }

    @Override
    public void mouseReleased(MouseEvent e) {

    }

    @Override
    public void mouseEntered(MouseEvent e) {

    }

    @Override
    public void mouseExited(MouseEvent e) {

    }

    /**
     * 获取
     * @return name
     */
    public String getName() {
        return name;
    }

    /**
     * 设置
     * @param name
     */
    public void setName(String name) {
        this.name = name;
    }

    /**
     * 获取
     * @return canClick
     */
    public boolean isCanClick() {
        return canClick;
    }

    /**
     * 设置
     * @param canClick
     */
    public void setCanClick(boolean canClick) {
        this.canClick = canClick;
    }

    /**
     * 获取
     * @return up
     */
    public boolean isUp() {
        return up;
    }

    /**
     * 设置
     * @param up
     */
    public void setUp(boolean up) {
        this.up = up;
    }

    /**
     * 获取
     * @return isClicked
     */
    public boolean isIsClicked() {
        return isClicked;
    }

    /**
     * 设置
     * @param isClicked
     */
    public void setIsClicked(boolean isClicked) {
        this.isClicked = isClicked;
    }

    public String toString() {
        if(name.equals("5-1")){
            return "BLACKJOKER";
        }
        if(name.equals("5-2")){
            return "REDJOKER";
        }
        return name.substring(2);
    }
}
