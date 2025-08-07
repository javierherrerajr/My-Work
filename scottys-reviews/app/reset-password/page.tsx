"use client";

import { Input } from "@/components/ui/input";
import { Button } from "@/components/ui/button";
import { useState, useEffect } from "react";
import { useSearchParams, useRouter } from "next/navigation";

export default function ResetPasswordPage() {
  const [password, setPassword] = useState("");
  const [error, setError] = useState("");
  const [success, setSuccess] = useState(false);
  const [loading, setLoading] = useState(false);
  const router = useRouter();
  const searchParams = useSearchParams();
  const token = searchParams.get("token");

  useEffect(() => {
    if (!token) {
      setError("Reset token is missing or invalid.");
    }
  }, [token]);

  const handleSubmit = async (e: React.FormEvent) => {
    e.preventDefault();
    setLoading(true);
    setError("");
    setSuccess(false);

    const res = await fetch("/api/auth/reset", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ token, newPassword: password }),
    });

    const data = await res.json();
    setLoading(false);

    if (!res.ok) {
      setError(data.error || "Something went wrong.");
    } else {
      setSuccess(true);
      setTimeout(() => router.push("/login?reset=success"), 2000);
    }
  };

  return (
    <div className="min-h-screen flex items-center justify-center bg-[#d6e2ce]">
      <div className="bg-[#f8f1e4] rounded-lg shadow-lg p-10 w-full max-w-md">
        <h1 className="text-3xl font-bold text-center mb-6 text-[#3a2c23]">Reset Password</h1>

        {error && <p className="text-red-600 font-semibold text-center mb-4">{error}</p>}
        {success && <p className="text-green-600 font-semibold text-center mb-4">✅ Password reset! Redirecting...</p>}

        <form onSubmit={handleSubmit}>
          <label htmlFor="password" className="block font-bold text-[#3a2c23] mb-2">New Password</label>
          <Input
            id="password"
            name="password"
            type="password"
            className="mb-6 bg-gray-200 w-full h-12 text-lg"
            required
            value={password}
            onChange={(e) => setPassword(e.target.value)}
          />

          <Button
            type="submit"
            className="w-full !bg-[#3a2c23] text-white text-lg font-bold !hover:bg-[#2a1c13]"
            disabled={loading || !token}
          >
            {loading ? "Resetting..." : "Reset Password"}
          </Button>
        </form>
      </div>
    </div>
  );
}
