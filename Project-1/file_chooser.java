import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

public class file_chooser {
    private static read_wave wav_reader;
    public static void main(String[] args) {
        JFrame frame = new JFrame("Project 1");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(800, 400);

        JButton button_wav = new JButton("Open .wav File");
        button_wav.setBounds(150, 70, 200, 100);

        JButton button_tif = new JButton("Open .tif File");
        button_tif.setBounds(150, 120, 200, 100);

        JButton button_back = new JButton("back");
        button_tif.setBounds(150, 120, 200, 100);

        JButton button_exit = new JButton("exit");
        button_tif.setBounds(150, 120, 200, 100);

        JFileChooser file_window_wav = new JFileChooser();

        FileNameExtensionFilter filter_wav = new FileNameExtensionFilter("WAV", "wav");
        file_window_wav.setFileFilter(filter_wav);


        JFileChooser file_window_tif = new JFileChooser();

        FileNameExtensionFilter filter_tif = new FileNameExtensionFilter("TIF", "tif");
        file_window_tif.setFileFilter(filter_tif);

        JPanel panel = new JPanel();
        panel.setLayout(new FlowLayout(FlowLayout.CENTER, 10, 10)); 
        panel.add(button_wav);
        panel.add(button_tif);
        panel.add(button_exit);
        frame.add(panel);
        frame.setVisible(true);

        button_wav.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int check = file_window_wav.showOpenDialog(null);
                if (check == JFileChooser.APPROVE_OPTION) {
                    File file = file_window_wav.getSelectedFile();
                    System.out.println("Selected .wav File: " + file.getPath());
                    //frame.getContentPane().removeAll();
                    wav_reader = new read_wave(file.getPath());
                    wav_reader.draw();
                    wav_reader.add(button_back);
                    frame.add(wav_reader);
                    button_tif.setVisible(false);
                    button_wav.setVisible(false);
                    button_exit.setVisible(false);
                    panel.setVisible(false);
                    button_back.setVisible(true);
                } else {
                    System.out.println("Cancel");
                }
            }
        });

        button_tif.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int check = file_window_tif.showOpenDialog(null);
                if (check == JFileChooser.APPROVE_OPTION) {
                    File file = file_window_tif.getSelectedFile();
                    System.out.println("Selected .tif File: " + file.getPath());
                } else {
                    System.out.println("cancel");
                }
            }
        });
        button_back.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                wav_reader.setVisible(false);
                panel.setVisible(true);
                button_tif.setVisible(true);
                button_wav.setVisible(true);
                button_exit.setVisible(true);
                
            }
        });

        button_exit.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        });
    }
}
