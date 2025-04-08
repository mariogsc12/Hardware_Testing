figure;
plot(control_action, speed, 'b-', 'LineWidth', 1.5); % línea azul

xlabel('Acción de control', 'FontSize', 12);
ylabel('Velocidad', 'FontSize', 12);
grid on;
title('Relación entre acción de control y velocidad');

% Opcional: mejora visual
set(gca, 'FontSize', 12);    % tamaño de fuente de los ejes
set(gcf, 'Color', 'w');      % fondo blanco

% === Guardar figura ===
saveas(gcf, 'accion_control_vs_velocidad.png');