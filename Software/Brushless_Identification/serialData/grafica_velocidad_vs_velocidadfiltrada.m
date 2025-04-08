% === Graficar velocidad real y filtrada respecto al tiempo ===
figure;
plot(time, speed, 'r-', 'LineWidth', 1.5); hold on;
plot(time, filtered_speed, 'b-', 'LineWidth', 1.5);

% === Personalización ===
xlabel('Tiempo (s)', 'FontSize', 12);
ylabel('Velocidad (rpm)', 'FontSize', 12);
title('Velocidad real y filtrada', 'FontWeight', 'bold');
legend('Velocidad real', 'Velocidad filtrada', 'Location', 'best');
grid on;
set(gca, 'FontSize', 12);
set(gcf, 'Color', 'w');

% === Guardar figura (opcional)
% saveas(gcf, 'velocidad_real_vs_filtrada.png');
