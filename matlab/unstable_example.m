% unstable_example.m
clear; clc; close all;

N = 40;

% --- Pre-allocate arrays ---
y_open = zeros(1, N);
x1a = zeros(1, N); % Closed Loop 1 (Stable)
x1b = zeros(1, N); % Closed Loop 2 (Very Unstable)

% --- Initial Conditions ---
% Matching your C++ logic: y[1] is first step, y[2] is second
y_open(1) = 1; 
y_open(2) = 0;

x1a(1) = y_open(1);
x1a(2) = y_open(2);

x1b(1) = y_open(1);
x1b(2) = y_open(2);

% --- Simulation Loop ---
for k = 2 : N-1
    % 1. Open Loop System (u = 0)
    y_open(k+1) = 1.3 * y_open(k) + 0.5 * y_open(k-1);
    
    % 2. Closed Loop 1 (Stable)
    k1a = 0.2; k2a = 0.8;
    u_a = -(k1a * x1a(k) + k2a * x1a(k-1));
    x1a(k+1) = 1.3 * x1a(k) + 0.5 * x1a(k-1) + u_a;
    
    % 3. Closed Loop 2 (Catastrophic)
    k1b = 2.5; k2b = 3;
    u_b = -(k1b * x1b(k) + k2b * x1b(k-1));
    x1b(k+1) = 1.3 * x1b(k) + 0.5 * x1b(k-1) + u_b;
end

% --- Visualization ---
t = 0:N-1;
figure('Color', 'w', 'Position', [100, 100, 800, 600]);

subplot(3,1,1);
stem(t, y_open, 'filled'); title('Open Loop (Unstable)'); grid on;
ylabel('Output');

subplot(3,1,2);
stem(t, x1a, 'filled', 'Color', [0 0.5 0]); title('Closed Loop 1 (Stable)'); grid on;
ylabel('Output');

subplot(3,1,3);
stem(t, x1b, 'filled', 'Color', 'r'); title('Closed Loop 2 (Catastrophic)'); grid on;
ylabel('Output');
xlabel('K (Time steps)');