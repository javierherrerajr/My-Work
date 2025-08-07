"use client";

import { useState } from "react";
import { Input } from "@/components/ui/input";
import { Button } from "@/components/ui/button";

export default function ForgotPasswordPage() {
  const [netid, setNetid] = useState("");
  const [message, setMessage] = useState("");
  const [resetUrl, setResetUrl] = useState("");

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();
    const res = await fetch("/api/auth/forgot", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ netid }),
    });
    const data = await res.json();
    setMessage(data.message || "Reset link created. Check logs.");
    if (data.resetUrl) {
      setResetUrl(data.resetUrl);
    }
  };

  return (
    <div className="min-h-screen flex items-center justify-center bg-[#d6e2ce]">
      <div className="bg-[#f8f1e4] rounded-lg shadow-lg p-10 w-full max-w-md">
        <h1 className="text-3xl font-bold text-center mb-6 text-[#3a2c23]">Forgot Password</h1>
        {message && <p className="text-center mb-4 text-green-600">{message}</p>}
        {resetUrl && (
            <p className="text-sm text-center mt-2 text-blue-600 underline break-all">
            Reset link: <a href={resetUrl} target="_blank" rel="noopener noreferrer">{resetUrl}</a>
            </p>
        )}
        <form onSubmit={handleSubmit}>
          <label className="block font-bold text-[#3a2c23] mb-2">Enter your NetID</label>
          <Input
            type="text"
            value={netid}
            onChange={(e) => setNetid(e.target.value)}
            className="mb-4 bg-gray-200 w-full h-12 text-lg"
            required
          />
          <Button type="submit" className="w-full !bg-[#3a2c23] text-white text-lg font-bold !hover:bg-[#2a1c13]">
            Request Reset Link
          </Button>
        </form>
      </div>
    </div>
  );
}
