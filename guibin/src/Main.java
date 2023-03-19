import java.awt.*;
import java.awt.event.ItemEvent;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;

public class Main {
    public static void main(String[] args) {
        new MyFrame().setVisible(true);
    }
}

class MyFrame extends JFrame {
    boolean reCompile = false;

    public MyFrame() {
        setTitle("Longest-Word-Chain");
        setSize(800, 600);
        setLocation(300, 200);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setResizable(false);
        setFrameLayout();
    }

    private void setFrameLayout() {
        JPanel panel1 = new JPanel();
        panel1.setLayout(null);
        panel1.setBounds(0, 0, 500, 300);
        add(panel1);


        JPanel panel2 = new JPanel();
        panel2.setLayout(null);
        panel2.setBounds(0, 300, 500, 300);
        add(panel2);

        JPanel panel3 = new JPanel();
        panel3.setLayout(null);
        panel3.setLocation(500, 0);
        add(panel3);


        /* 输入文本域设置 */
        JLabel inputLabel = new JLabel("输入框");
        inputLabel.setBounds(50, 30, 40, 20);
        panel1.add(inputLabel);
        JTextArea inputArea = new JTextArea();
        JScrollPane inputScrollPane = new JScrollPane(inputArea);   // 滚动条
        inputArea.setLineWrap(false);
        inputScrollPane.setBounds(50, 50, 400, 200);
        panel1.add(inputScrollPane);

        /* 输出文本域设置 */
        JLabel outputLabel = new JLabel("输出框");
        outputLabel.setBounds(50, 0, 40, 20);
        panel2.add(outputLabel);
        JTextArea outputArea = new JTextArea();
        outputArea.setEditable(false);
        JScrollPane outputScrollPane = new JScrollPane(outputArea);   // 滚动条
        outputArea.setLineWrap(false);
        outputScrollPane.setBounds(50, 20, 400, 200);
        panel2.add(outputScrollPane);

        /* 文件选择器FileChooser */
        JButton fileChooseButton = new JButton("选择文件");
        fileChooseButton.setBounds(50, 260, 100, 30);
        fileChooseButton.addActionListener(e -> {
            JFileChooser fileChooser = new JFileChooser();
            FileNameExtensionFilter filter = new FileNameExtensionFilter("Text Files", "txt");
            fileChooser.setFileFilter(filter);
            if (fileChooser.showOpenDialog(panel1) == JFileChooser.APPROVE_OPTION) {
                // Get the selected file
                java.io.File selectedFile = fileChooser.getSelectedFile();
                System.out.println("Selected file: " + selectedFile.getAbsolutePath());
                String context = readTxtFile(selectedFile.getAbsolutePath(), false);
                inputArea.setText(context);
            }
        });
        panel1.add(fileChooseButton);

        /* 将输出框内容保存为文件 */
        JButton saveButton = new JButton("保存文件");
        saveButton.addActionListener(e -> {
            // 创建一个文件选择器，让用户选择保存文件的路径
            JFileChooser fileChooser = new JFileChooser();
            fileChooser.setDialogTitle("选择保存路径");
            fileChooser.setFileFilter(new FileNameExtensionFilter("Text files", "txt"));
            int userSelection = fileChooser.showSaveDialog(this);
            if (userSelection == JFileChooser.APPROVE_OPTION) {
                // 获取用户选择的文件路径
                File fileToSave = fileChooser.getSelectedFile();
                if (!fileToSave.getName().endsWith(".txt")) {
                    // 如果不是，弹出提示框，提示用户选择一个 .txt 文件
                    JOptionPane.showMessageDialog(this, "请选择一个 .txt 格式的文件！");
                } else {
                    try {
                        FileWriter writer = new FileWriter(fileToSave);
                        writer.write(outputArea.getText());
                        writer.close();
                        JOptionPane.showMessageDialog(this, "文件保存成功！");
                    } catch (IOException ex) {
                        JOptionPane.showMessageDialog(this, "保存文件失败：" + ex.getMessage());
                    }
                }
            }
        });
        saveButton.setBounds(50, 230, 100, 30);
        panel2.add(saveButton);

        /* 执行时间Label */
        JLabel timeLabel = new JLabel("程序执行时间");
        timeLabel.setBackground(Color.BLACK);
        timeLabel.setBounds(170, 230, 150, 30);
        panel2.add(timeLabel);


        /* 添加多选框 */
        JLabel multiple = new JLabel("功能参数选择");
        JCheckBox checkBox_n = new JCheckBox("-n");
        JCheckBox checkBox_w = new JCheckBox("-w");
        JCheckBox checkBox_c = new JCheckBox("-c");
        JCheckBox checkBox_h = new JCheckBox("-h");
        JCheckBox checkBox_t = new JCheckBox("-t");
        JCheckBox checkBox_j = new JCheckBox("-j");
        JCheckBox checkBox_r = new JCheckBox("-r");
        panel3.add(multiple);
        panel3.add(checkBox_n);
        panel3.add(checkBox_w);
        panel3.add(checkBox_c);
        panel3.add(checkBox_h);
        panel3.add(checkBox_t);
        panel3.add(checkBox_j);
        panel3.add(checkBox_r);
        int x_offset = 0, y_offset = 100, width = 50, height = 20;
        multiple.setBounds(550, 160, 100, 20);
        checkBox_n.setBounds(x_offset + 550, y_offset + 100, width, height);
        checkBox_w.setBounds(x_offset + 550, y_offset + 140, width, height);
        checkBox_c.setBounds(x_offset + 550, y_offset + 180, width, height);
        checkBox_h.setBounds(x_offset + 550, y_offset + 220, width, height);
        checkBox_t.setBounds(x_offset + 550, y_offset + 260, width, height);
        checkBox_j.setBounds(x_offset + 550, y_offset + 300, width, height);
        checkBox_r.setBounds(x_offset + 550, y_offset + 340, width, height);

        /* 字母选择框 */
        String[] options = new String[]{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k",
                "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
        JComboBox<String> comboBox_h = new JComboBox<>(options);
        comboBox_h.setBounds(x_offset + 600, y_offset + 220, width + 50, 20);
        panel3.add(comboBox_h);
        JComboBox<String> comboBox_t = new JComboBox<>(options);
        comboBox_t.setBounds(x_offset + 600, y_offset + 260, width + 50, 20);
        panel3.add(comboBox_t);
        JComboBox<String> comboBox_j = new JComboBox<>(options);
        comboBox_j.setBounds(x_offset + 600, y_offset + 300, width + 50, 20);
        panel3.add(comboBox_j);

        /* 主动屏蔽冲突参数 */
        checkBox_n.addItemListener(e -> {
            if (e.getStateChange() == ItemEvent.SELECTED) {
                checkBox_w.setEnabled(false);
                checkBox_c.setEnabled(false);
                checkBox_h.setEnabled(false);
                checkBox_t.setEnabled(false);
                checkBox_j.setEnabled(false);
                checkBox_r.setEnabled(false);
                comboBox_h.setEnabled(false);
                comboBox_t.setEnabled(false);
                comboBox_j.setEnabled(false);
            } else {
                checkBox_w.setEnabled(true);
                checkBox_c.setEnabled(true);
            }
        });

        checkBox_w.addItemListener(e -> {
            if (e.getStateChange() == ItemEvent.SELECTED) {
                checkBox_n.setEnabled(false);
                checkBox_c.setEnabled(false);
                checkBox_h.setEnabled(true);
                checkBox_t.setEnabled(true);
                checkBox_j.setEnabled(true);
                checkBox_r.setEnabled(true);
                comboBox_h.setEnabled(true);
                comboBox_t.setEnabled(true);
                comboBox_j.setEnabled(true);
            } else {
                checkBox_n.setEnabled(true);
                checkBox_c.setEnabled(true);
                checkBox_h.setEnabled(false);
                checkBox_t.setEnabled(false);
                checkBox_j.setEnabled(false);
                checkBox_r.setEnabled(false);
                comboBox_h.setEnabled(false);
                comboBox_t.setEnabled(false);
                comboBox_j.setEnabled(false);
            }
        });

        checkBox_c.addItemListener(e -> {
            if (e.getStateChange() == ItemEvent.SELECTED) {
                checkBox_n.setEnabled(false);
                checkBox_w.setEnabled(false);
                checkBox_h.setEnabled(true);
                checkBox_t.setEnabled(true);
                checkBox_j.setEnabled(true);
                checkBox_r.setEnabled(true);
                comboBox_h.setEnabled(true);
                comboBox_t.setEnabled(true);
                comboBox_j.setEnabled(true);
            } else {
                checkBox_n.setEnabled(true);
                checkBox_w.setEnabled(true);
                checkBox_h.setEnabled(false);
                checkBox_t.setEnabled(false);
                checkBox_j.setEnabled(false);
                checkBox_r.setEnabled(false);
                comboBox_h.setEnabled(false);
                comboBox_t.setEnabled(false);
                comboBox_j.setEnabled(false);
            }
        });

        /* 选择框初始状态 */
        checkBox_h.setEnabled(false);
        checkBox_t.setEnabled(false);
        checkBox_j.setEnabled(false);
        checkBox_r.setEnabled(false);
        comboBox_h.setEnabled(false);
        comboBox_t.setEnabled(false);
        comboBox_j.setEnabled(false);

        /* 文件执行按钮 */
        JButton executeButton = new JButton("执行程序");
        executeButton.setBounds(150, 260, 100, 30);
        executeButton.addActionListener(e -> {
            if (!checkBox_n.isSelected() && !checkBox_w.isSelected() && !checkBox_c.isSelected()) {
                outputArea.setText("请在右侧选择执行参数");
                return;
            }
            String data = inputArea.getText();
            try {
                FileWriter writer = new FileWriter("input.txt");
                writer.write(data);
                writer.close();
            } catch (IOException e1) {
                e1.printStackTrace();
            }
            try {
                timeLabel.setText("程序正在执行...");
                outputArea.setText("");
                long startTime = System.currentTimeMillis();
                FileIO.parse_words(inputArea.getText());
                String[] words = FileIO.get_words();
                int len = words.length;
                // 运行函数
                if (checkBox_n.isSelected()) {
                    String[][] result = new String[20000][];
                    int ret = CoreAPI.genChainsAll(words, len, result);
                    if (ret == -1) {
                        outputArea.setText("输入存在非法环");
                        return;
                    }
                    outputArea.append(ret + "\n");
                    for (int i = 0; i < ret; i++) {
                        int length = result[i].length;
                        for (int j = 0; j < length; j++) {
                            outputArea.append(result[i][j] + " ");
                        }
                        outputArea.append("\n");
                    }
                } else {
                    char h = 0, t = 0, j = 0;
                    if (checkBox_h.isSelected()) {
                        if (comboBox_h.getSelectedItem() != null) {
                            h = comboBox_h.getSelectedItem().toString().charAt(0);
                        }
                    }
                    if (checkBox_t.isSelected()) {
                        if (comboBox_t.getSelectedItem() != null) {
                            t = comboBox_t.getSelectedItem().toString().charAt(0);
                        }
                    }
                    if (checkBox_j.isSelected()) {
                        if (comboBox_j.getSelectedItem() != null) {
                            j = comboBox_j.getSelectedItem().toString().charAt(0);
                        }
                    }
                    String[] result = new String[10005];
                    int ret;
                    if (checkBox_w.isSelected()) {
                        ret = CoreAPI.genChainWord(words, len, result, h, t, j, checkBox_r.isSelected());
                    } else {
                        ret = CoreAPI.genChainChar(words, len, result, h, t, j, checkBox_r.isSelected());
                    }
                    if (ret == -1) {
                        outputArea.setText("输入存在非法环");
                        return;
                    }
                    for (int i = 0; i < ret; i++) {
                        outputArea.append(result[i] + "\n");
                    }
                }
                long endTime = System.currentTimeMillis();
                double totalTimeInSeconds = (endTime - startTime) / 1000.0;
                String formattedRunTime = String.format("%.2f", totalTimeInSeconds);
                timeLabel.setText("程序执行时间为：" + formattedRunTime + "s\n");
            } catch (Exception ex) {
                throw new RuntimeException(ex);
            }
        });
        panel1.add(executeButton);
    }
    private String readTxtFile(String filepath, boolean changeLine) {
        StringBuilder str = new StringBuilder();
        try (BufferedReader br = new BufferedReader(new FileReader(filepath))) {
            if (changeLine) {
                String line;
                while ((line = br.readLine()) != null) {
                    str.append(line);
                    str.append("\n");
                }
            } else {
                String line;
                while ((line = br.readLine()) != null) {
                    str.append(line);
                }
            }
        } catch (IOException e) {
            System.err.println("Failed to read file: " + e.getMessage());
        }
        return str.toString();
    }
}