// AI-GENERATED

let wasmReady = false;
let wasmModule = null;

// Initialize WASM module
async function initWasm() {
    try {
        // Module is a function with MODULARIZE=1, call it
        wasmModule = await Module();
        
        wasmReady = true;
        addOutput('Virtual filesystem ready.', 'success');
    } catch (e) {
        addOutput('Error loading WASM: ' + e.message, 'error');
        console.error(e);
    }
}

// Start initialization when page loads
if (typeof Module !== 'undefined') {
    initWasm();
} else {
    window.addEventListener('load', function() {
        if (typeof Module !== 'undefined') {
            initWasm();
        } else {
            addOutput('Error: Module not found. Make sure main.js is loaded.', 'error');
        }
    });
}

function addOutput(text, className = '') {
    const output = document.getElementById('output');
    const line = document.createElement('div');
    line.className = 'output-line ' + className;
    line.textContent = text;
    output.appendChild(line);
    output.scrollTop = output.scrollHeight;
}

function executeCommand() {
    const input = document.getElementById('command-input');
    const command = input.value.trim();
    
    if (!command) return;
    
    if (!wasmReady) {
        addOutput('WASM not ready yet. Please wait...', 'error');
        return;
    }
    
    // Show the command with prompt
    addOutput('$ ' + command);
    
    // Parse and execute
    const parts = command.split(/\s+/);
    const cmd = parts[0];
    const args = parts.slice(1);
    
    try {
        switch(cmd) {
            case 'mkdir':
                if (args.length !== 1) {
                    addOutput('Usage: mkdir <path>', 'error');
                    break;
                }
                const mkdirResult = wasmModule.mkdir(args[0]);
                if (mkdirResult) {
                    addOutput('Directory created: ' + args[0], 'success');
                } else {
                    addOutput('Failed to create directory: ' + args[0], 'error');
                }
                break;
                
            case 'touch':
                if (args.length < 2) {
                    addOutput('Usage: touch <path> <file1> [file2] ...', 'error');
                    break;
                }
                const path = args[0];
                const files = args.slice(1);
                
                // Convert JS array to C++ vector
                const fileVec = new wasmModule.VectorString();
                for (let f of files) {
                    fileVec.push_back(f);
                }
                
                const touchResult = wasmModule.touch(path, fileVec);
                fileVec.delete();
                
                if (touchResult) {
                    addOutput('Files created: ' + files.join(', '), 'success');
                } else {
                    addOutput('Failed to create files', 'error');
                }
                break;
                
            case 'ls':
                if (args.length !== 1) {
                    addOutput('Usage: ls <path>', 'error');
                    break;
                }
                const lsResult = wasmModule.ls(args[0]);
                if (lsResult && lsResult.size() > 0) {
                    let output = '';
                    for (let i = 0; i < lsResult.size(); i++) {
                        output += lsResult.get(i) + '  ';
                    }
                    addOutput(output);
                    lsResult.delete();
                } else {
                    addOutput('(empty)', 'error');
                }
                break;
                
            case 'mv':
                if (args.length !== 2) {
                    addOutput('Usage: mv <src> <dst>', 'error');
                    break;
                }
                const mvResult = wasmModule.mv(args[0], args[1]);
                if (mvResult) {
                    addOutput('Moved: ' + args[0] + ' -> ' + args[1], 'success');
                } else {
                    addOutput('Failed to move: ' + args[0], 'error');
                }
                break;
                
            case 'echo':
                if (args.length === 0) {
                    addOutput('Usage: echo <text>', 'error');
                    break;
                }
                const text = args.join(' ');
                const echoResult = wasmModule.echo(text);
                addOutput(echoResult);
                break;
                
            default:
                addOutput('Unknown command: ' + cmd, 'error');
                addOutput('Available: mkdir, touch, ls, mv, echo', 'prompt');
        }
    } catch (e) {
        addOutput('Error: ' + e.message, 'error');
        console.error(e);
    }
    
    input.value = '';
}

// Allow Enter key to execute
document.getElementById('command-input').addEventListener('keypress', function(e) {
    if (e.key === 'Enter') {
        executeCommand();
    }
});

