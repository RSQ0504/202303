import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Hashtable;

public class RGBColorSliderWithInput {
    private static JLabel redValueLabel;
    private static JLabel greenValueLabel;
    private static JLabel blueValueLabel;
    private static JTextField redInput;
    private static JTextField greenInput;
    private static JTextField blueInput;

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            createAndShowGUI();
        });
    }

    private static void createAndShowGUI() {
        JFrame frame = new JFrame("RGB Color Slider");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 400);

        JPanel panel = new JPanel();
        frame.add(panel);

        JLabel label = new JLabel("RGB Color:");
        panel.add(label);

        JSlider redSlider = createSlider("Red", 0, 255, 128);
        JSlider greenSlider = createSlider("Green", 0, 255, 128);
        JSlider blueSlider = createSlider("Blue", 0, 255, 128);

        panel.add(redSlider);
        panel.add(greenSlider);
        panel.add(blueSlider);

        JPanel colorPanel = new JPanel();
        colorPanel.setPreferredSize(new Dimension(200, 100));
        panel.add(colorPanel);

        redValueLabel = createValueLabel("Red: " + redSlider.getValue());
        greenValueLabel = createValueLabel("Green: " + greenSlider.getValue());
        blueValueLabel = createValueLabel("Blue: " + blueSlider.getValue());

        panel.add(redValueLabel);
        panel.add(greenValueLabel);
        panel.add(blueValueLabel);

        redInput = createInputField("Red:", redSlider.getValue());
        greenInput = createInputField("Green:", greenSlider.getValue());
        blueInput = createInputField("Blue:", blueSlider.getValue());

        panel.add(redInput);
        panel.add(greenInput);
        panel.add(blueInput);

        redSlider.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                int redValue = redSlider.getValue();
                redValueLabel.setText("Red: " + redValue);
                redInput.setText(String.valueOf(redValue));
                updateColor(colorPanel, redValue, greenSlider.getValue(), blueSlider.getValue());
            }
        });

        greenSlider.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                int greenValue = greenSlider.getValue();
                greenValueLabel.setText("Green: " + greenValue);
                greenInput.setText(String.valueOf(greenValue));
                updateColor(colorPanel, redSlider.getValue(), greenValue, blueSlider.getValue());
            }
        });

        blueSlider.addChangeListener(new ChangeListener() {
            @Override
            public void stateChanged(ChangeEvent e) {
                int blueValue = blueSlider.getValue();
                blueValueLabel.setText("Blue: " + blueValue);
                blueInput.setText(String.valueOf(blueValue));
                updateColor(colorPanel, redSlider.getValue(), greenSlider.getValue(), blueValue);
            }
        });

        redInput.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    int redValue = Integer.parseInt(redInput.getText());
                    if (redValue >= 0 && redValue <= 255) {
                        redSlider.setValue(redValue);
                    } else {
                        redInput.setText(String.valueOf(redSlider.getValue()));
                    }
                } catch (NumberFormatException ex) {
                    redInput.setText(String.valueOf(redSlider.getValue()));
                }
            }
        });

        greenInput.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    int greenValue = Integer.parseInt(greenInput.getText());
                    if (greenValue >= 0 && greenValue <= 255) {
                        greenSlider.setValue(greenValue);
                    } else {
                        greenInput.setText(String.valueOf(greenSlider.getValue()));
                    }
                } catch (NumberFormatException ex) {
                    greenInput.setText(String.valueOf(greenSlider.getValue()));
                }
            }
        });

        blueInput.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    int blueValue = Integer.parseInt(blueInput.getText());
                    if (blueValue >= 0 && blueValue <= 255) {
                        blueSlider.setValue(blueValue);
                    } else {
                        blueInput.setText(String.valueOf(blueSlider.getValue()));
                    }
                } catch (NumberFormatException ex) {
                    blueInput.setText(String.valueOf(blueSlider.getValue()));
                }
            }
        });

        frame.setVisible(true);
    }

    private static JSlider createSlider(String label, int min, int max, int initial) {
        JSlider slider = new JSlider(JSlider.HORIZONTAL, min, max, initial);
        slider.setPaintLabels(true);
        slider.setPaintTicks(true);
        slider.setMajorTickSpacing(50);
        slider.setMinorTickSpacing(10);
        slider.setBorder(BorderFactory.createTitledBorder(label));

        // Add labels at the beginning and end of the slider
        Hashtable<Integer, JLabel> labelTable = new Hashtable<>();
        labelTable.put(min, new JLabel(String.valueOf(min)));
        labelTable.put(max, new JLabel(String.valueOf(max)));
        slider.setLabelTable(labelTable);

        return slider;
    }

    private static JLabel createValueLabel(String text) {
        JLabel label = new JLabel(text);
        label.setHorizontalAlignment(JLabel.CENTER);
        return label;
    }

    private static JTextField createInputField(String label, int initialValue) {
        JTextField textField = new JTextField(4);
        textField.setHorizontalAlignment(JTextField.CENTER);
        textField.setText(String.valueOf(initialValue));
        JLabel inputLabel = new JLabel(label);
        inputLabel.setLabelFor(textField);
        return textField;
    }

    private static void updateColor(JPanel colorPanel, int red, int green, int blue) {
        Color color = new Color(red, green, blue);
        colorPanel.setBackground(color);
    }
}
