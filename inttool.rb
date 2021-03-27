#!/usr/bin/env ruby

def spawn_process(cmd)

	in_r, in_w = IO.pipe
	out_r, out_w = IO.pipe
	err_r, err_w = IO.pipe
	pid = spawn(*cmd, in: in_r, out: out_w, err: err_w)
	in_r.close
	out_w.close
	err_w.close

	return [pid, in_w, out_r, err_r]

end

def intercept(src, dest, &block)
	loop do
		begin
			line = src.readline
		rescue EOFError
			dest.close if !dest.nil?
			return
		end
		block.call(line.strip)
		begin
			dest.write(line) if !dest.nil?
		rescue Errno::EPIPE
			src.close if !src.nil?
			return
		end
		10.times do
			Thread.pass
		end
	end
end

def start_interception(src, dest, &block)
	t = Thread.new do
		intercept(src, dest, &block)
	end
end

def start_wait(pid, &block)
	t = Thread.new do
		_, st = Process.waitpid2(pid)
		block.call(st.success?)
	end
end

def start(cmd1, cmd2)

	pid1, in1, out1, err1 = spawn_process(cmd1)
	pid2, in2, out2, err2 = spawn_process(cmd2)

	t1 = start_interception(out1, in2) do |line|
		puts "\e[2m==> #{line}\e[m"
	end
	t2 = start_interception(out2, in1) do |line|
		puts "\e[2m<== #{line}\e[m"
	end
	t3 = start_interception(err1, nil) do |line|
		puts "$ #{line}"
	end
	t4 = start_interception(err2, nil) do |line|
		puts "# #{line}"
	end
	t5 = start_wait(pid1) do |ok|
		color = ok ? "2" : "1"
		puts "\e[3#{color}m$ left exited\e[m"
	end
	t6 = start_wait(pid2) do |ok|
		color = ok ? "2" : "1"
		puts "\e[3#{color}m# right exited\e[m"
	end

	[t1, t2, t3, t4, t5, t6].each do |t|
		t.join
	end

end

if __FILE__ == $0
	if ARGV.length < 3 || ARGV.count("--") != 1
		$stderr.puts "example: #{$0} ./a 10 -- python3 test.py"
		exit 1
	end
	mid = ARGV.index("--")
	left = ARGV[0...mid]
	right = ARGV[(mid+1)..-1]
	start(left, right)
end
