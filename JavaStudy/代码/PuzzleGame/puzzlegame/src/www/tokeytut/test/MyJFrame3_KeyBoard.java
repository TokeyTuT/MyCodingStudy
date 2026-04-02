package www.tokeytut.test;

import javax.swing.*;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;

public class MyJFrame3_KeyBoard extends JFrame implements KeyListener {
    MyJFrame3_KeyBoard(){
        this.setSize(500,500);
        this.setTitle("键盘监听");
        this.setAlwaysOnTop(true);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setLayout(null);
        this.setLocationRelativeTo(null);

        this.addKeyListener(this);

        this.setVisible(true);
    }

    @Override
    public void keyTyped(KeyEvent e) {
        //没什么用，一般不重写
    }

    @Override
    public void keyPressed(KeyEvent e) {
        System.out.println("输入了"+e.getKeyCode());
    }

    @Override
    public void keyReleased(KeyEvent e) {
        System.out.println("释放了"+e.getKeyCode());
    }
}
