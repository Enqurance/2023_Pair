import java.awt.*;

import javax.swing.*;


public class Main {
    public static void main(String[] args) {
        new MyFrame();
    }
}

class MyFrame extends JFrame {
    public MyFrame() {
        setTitle("Longest-Word-Chain");
        setSize(1000, 800);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        Container c = getContentPane();
        setVisible(true);       // 设置窗口可见性
        setLayout(new BorderLayout());

        JPanel panel1 = new JPanel();
        panel1.setBackground(Color.CYAN);
        panel1.setSize();
        JButton button2 = new JButton("左·写菜单的比较多，但不一定用");
        JButton button3 = new JButton("中·表格信息");
        JButton button4 = new JButton("右·很少用到");
        JButton button5 = new JButton("下·备案号啥的");
        //上n下s左w右e中center
        add(panel1, BorderLayout.NORTH);
        add(button2, BorderLayout.WEST);
        add(button3, BorderLayout.CENTER);
        add(button4, BorderLayout.EAST);
        add(button5, BorderLayout.SOUTH);
        setBounds(300, 200, 600, 300);
    }

}