package www.tokeytut.test;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Random;

public class MyJFrame1_ActionListener extends JFrame implements ActionListener {
    final private JButton jb1 = new JButton("Button1");
    final private JButton jb2 = new JButton("Button2");
    MyJFrame1_ActionListener(){
        this.setSize(500,500);
        this.setTitle("测试按钮 2");
        this.setAlwaysOnTop(true);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setLocationRelativeTo(null);
        this.setLayout(null);



        jb1.setBounds(0,0,100,100);
        jb2.setBounds(100,0,100,100);

        jb1.addActionListener(this);
        jb2.addActionListener(this);

        this.getContentPane().add(jb1);
        this.getContentPane().add(jb2);

        this.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        Object sc = e.getSource();
        Random r = new Random();
        if(sc == jb1){
            jb1.setBounds(r.nextInt(500),r.nextInt(500),100,100);
        }else{
            jb2.setSize(r.nextInt(200),r.nextInt(200));
        }
    }
}
