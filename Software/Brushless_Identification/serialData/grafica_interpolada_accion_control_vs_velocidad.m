% === Datos de entrada ===
% Asegúrate de que estas variables ya estén en el workspace:
% control_action (vector)
% speed (vector)

% === Cálculo de puntos medios por escalón ===
jumps = [1; find(diff(control_action) ~= 0) + 1; length(control_action) + 1];
x_avg = zeros(length(jumps)-1,1);
y_avg = zeros(length(jumps)-1,1);

for i = 1:length(jumps)-1
    idx = jumps(i):jumps(i+1)-1;
    x_avg(i) = mean(control_action(idx));
    y_avg(i) = mean(speed(idx));
end

% === Crear figura ===
figure;
hold on;

% === Dibujar líneas conectando puntos medios, excepto entre -10 y 0 ===
for i = 1:length(x_avg)-1
    x1 = x_avg(i);
    x2 = x_avg(i+1);
    y1 = y_avg(i);
    y2 = y_avg(i+1);

    % Omitir la conexión entre -10 y 0
    if ~( (x1 <= -10 && x2 >= 0) || (x1 >= 0 && x2 <= -10) )
        plot([x1, x2], [y1, y2], 'b-', 'LineWidth', 2);  % Azul
    end
end

% === Añadir segmento especial entre -10 y 0 (con velocidad -16.92) ===
i_neg10 = find(abs(x_avg + 10) < 0.1); % tolerancia por si no es exactamente -10
if ~isempty(i_neg10)
    x_neg10 = x_avg(i_neg10);
    y_neg10 = y_avg(i_neg10);

    % Conectar hasta PWM = 0, velocidad = -16.92
    plot([x_neg10, 0], [y_neg10, -16.5], 'b-', 'LineWidth', 2);  % Azul
end

% === Línea vertical de zona muerta en PWM = 0 ===
plot([0, 0], [-16.5, 40.96], 'b-', 'LineWidth', 2);  % Azul

% === Etiquetas y estilo ===
xlabel('Acción de control (PWM)', 'FontSize', 12);
ylabel('Velocidad (rpm)', 'FontSize', 12);
title('Relación entre acción de control y velocidad', 'FontWeight', 'bold');

grid on;
set(gca, 'FontSize', 12);
set(gcf, 'Color', 'w');

% === Guardar figura ===
saveas(gcf, 'accion_control_vs_velocidad_final.png');


